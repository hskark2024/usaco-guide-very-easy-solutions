#!/usr/bin/env python3
"""Render one simple narrated slide video from a prepared Easy package."""

from pathlib import Path
import argparse
import re
import shutil
import subprocess
import tempfile


def run(command: list[str]) -> None:
    subprocess.run(command, check=True)


def main() -> None:
    parser = argparse.ArgumentParser()
    parser.add_argument("folder", type=Path)
    parser.add_argument("--voice", default="Daniel")
    args = parser.parse_args()
    folder = args.folder.resolve()

    slides = []
    for line in (folder / "slides.tsv").read_text().splitlines():
        title, *bullets = line.split("\t")
        slides.append((title, bullets))
    if not slides:
        raise SystemExit("slides.tsv has no slides")

    audio = folder / "narration.aiff"
    video = folder / "video.mp4"
    run(["say", "-v", args.voice, "-f", str(folder / "narration.txt"), "-o", str(audio)])
    ffmpeg = shutil.which("ffmpeg")
    if ffmpeg is None:
        try:
            import imageio_ffmpeg
        except ImportError as error:
            raise SystemExit(
                "ffmpeg is unavailable; install imageio-ffmpeg or add ffmpeg to PATH"
            ) from error
        ffmpeg = imageio_ffmpeg.get_ffmpeg_exe()

    audio_info = subprocess.check_output(["afinfo", str(audio)], text=True)
    match = re.search(r"estimated duration: ([0-9.]+) sec", audio_info)
    if match is None:
        raise SystemExit("could not read narration duration from afinfo")
    duration = float(match.group(1))
    seconds_per_slide = max(1.0, duration / len(slides))

    font = "/System/Library/Fonts/Supplemental/Arial.ttf"
    with tempfile.TemporaryDirectory(prefix="usaco-slides-") as temp_name:
        temp = Path(temp_name)
        concat_lines = []
        for index, (title, bullets) in enumerate(slides):
            title_file = temp / f"title-{index}.txt"
            body_file = temp / f"body-{index}.txt"
            image_file = temp / f"slide-{index}.png"
            title_file.write_text(title)
            body_file.write_text("\n\n".join(f"• {bullet}" for bullet in bullets))
            filters = (
                f"drawtext=fontfile='{font}':textfile='{title_file}':"
                "fontcolor=0xF7C948:fontsize=48:x=80:y=90,"
                f"drawtext=fontfile='{font}':textfile='{body_file}':"
                "fontcolor=white:fontsize=32:line_spacing=15:x=105:y=215"
            )
            run([
                ffmpeg, "-loglevel", "error", "-y", "-f", "lavfi", "-i",
                "color=c=0x10182B:s=1280x720", "-vf", filters, "-frames:v", "1",
                str(image_file),
            ])
            concat_lines.extend([f"file '{image_file}'", f"duration {seconds_per_slide:.6f}"])
        concat_lines.append(f"file '{temp / f'slide-{len(slides) - 1}.png'}'")
        concat_file = temp / "slides.ffconcat"
        concat_file.write_text("ffconcat version 1.0\n" + "\n".join(concat_lines) + "\n")
        run([
            ffmpeg, "-loglevel", "error", "-y", "-f", "concat", "-safe", "0",
            "-i", str(concat_file), "-i", str(audio), "-c:v", "libx264",
            "-pix_fmt", "yuv420p", "-r", "30", "-c:a", "aac", "-b:a", "160k",
            "-shortest", str(video),
        ])

    print(f"rendered {video} ({duration:.1f}s narration, {len(slides)} slides)")


if __name__ == "__main__":
    main()
