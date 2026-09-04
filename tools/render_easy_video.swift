#!/usr/bin/env swift

import AppKit
import AVFoundation
import CoreVideo
import Foundation

struct Slide {
    let title: String
    let bullets: [String]
}

func fail(_ message: String) -> Never {
    FileHandle.standardError.write(Data(("error: \(message)\n").utf8))
    exit(1)
}

guard CommandLine.arguments.count == 4 else {
    fail("usage: render_easy_video.swift slides.tsv narration.aiff output.mp4")
}

let slidesURL = URL(fileURLWithPath: CommandLine.arguments[1])
let audioURL = URL(fileURLWithPath: CommandLine.arguments[2])
let outputURL = URL(fileURLWithPath: CommandLine.arguments[3])

let slideText: String
do {
    slideText = try String(contentsOf: slidesURL, encoding: .utf8)
} catch {
    fail("could not read slides: \(error)")
}

let slides = slideText.split(whereSeparator: \Character.isNewline).compactMap { line -> Slide? in
    let fields = line.split(separator: "\t", maxSplits: 1, omittingEmptySubsequences: false)
    guard fields.count == 2 else { return nil }
    return Slide(
        title: String(fields[0]),
        bullets: fields[1].split(separator: "|", omittingEmptySubsequences: true).map(String.init)
    )
}
guard !slides.isEmpty else { fail("slides.tsv contains no valid slides") }

let audioAsset = AVURLAsset(url: audioURL)
let audioDuration = CMTimeGetSeconds(audioAsset.duration)
guard audioDuration.isFinite && audioDuration > 0 else { fail("narration has no readable duration") }

let manager = FileManager.default
let temporaryVideoURL = manager.temporaryDirectory.appendingPathComponent(UUID().uuidString + ".mov")
try? manager.removeItem(at: temporaryVideoURL)
try? manager.removeItem(at: outputURL)

let width = 1280
let height = 720
let fps: Int32 = 2
let frameCount = Int(ceil(audioDuration * Double(fps)))

let writer: AVAssetWriter
do {
    writer = try AVAssetWriter(outputURL: temporaryVideoURL, fileType: .mov)
} catch {
    fail("could not create video writer: \(error)")
}

let videoSettings: [String: Any] = [
    AVVideoCodecKey: AVVideoCodecType.h264,
    AVVideoWidthKey: width,
    AVVideoHeightKey: height,
    AVVideoCompressionPropertiesKey: [
        AVVideoAverageBitRateKey: 1_200_000,
        AVVideoProfileLevelKey: AVVideoProfileLevelH264HighAutoLevel,
    ],
]
let writerInput = AVAssetWriterInput(mediaType: .video, outputSettings: videoSettings)
writerInput.expectsMediaDataInRealTime = false
let adaptor = AVAssetWriterInputPixelBufferAdaptor(
    assetWriterInput: writerInput,
    sourcePixelBufferAttributes: [
        kCVPixelBufferPixelFormatTypeKey as String: kCVPixelFormatType_32BGRA,
        kCVPixelBufferWidthKey as String: width,
        kCVPixelBufferHeightKey as String: height,
    ]
)
guard writer.canAdd(writerInput) else { fail("video writer rejected its input") }
writer.add(writerInput)
guard writer.startWriting() else { fail("video writer could not start: \(writer.error?.localizedDescription ?? "unknown")") }
writer.startSession(atSourceTime: .zero)
guard let pool = adaptor.pixelBufferPool else { fail("video writer did not create a pixel buffer pool") }

func draw(_ slide: Slide, number: Int, total: Int, into buffer: CVPixelBuffer) {
    CVPixelBufferLockBaseAddress(buffer, [])
    defer { CVPixelBufferUnlockBaseAddress(buffer, []) }

    guard let base = CVPixelBufferGetBaseAddress(buffer) else { return }
    let bytesPerRow = CVPixelBufferGetBytesPerRow(buffer)
    guard let context = CGContext(
        data: base,
        width: width,
        height: height,
        bitsPerComponent: 8,
        bytesPerRow: bytesPerRow,
        space: CGColorSpaceCreateDeviceRGB(),
        bitmapInfo: CGImageAlphaInfo.premultipliedFirst.rawValue | CGBitmapInfo.byteOrder32Little.rawValue
    ) else { return }

    let colors = [
        CGColor(red: 0.035, green: 0.075, blue: 0.16, alpha: 1),
        CGColor(red: 0.06, green: 0.18, blue: 0.28, alpha: 1),
    ] as CFArray
    let gradient = CGGradient(colorsSpace: CGColorSpaceCreateDeviceRGB(), colors: colors, locations: [0, 1])!
    context.drawLinearGradient(
        gradient,
        start: CGPoint(x: 0, y: height),
        end: CGPoint(x: width, y: 0),
        options: []
    )

    context.setFillColor(CGColor(red: 0.14, green: 0.78, blue: 0.68, alpha: 1))
    context.fill(CGRect(x: 70, y: height - 102, width: 120, height: 8))

    let graphics = NSGraphicsContext(cgContext: context, flipped: false)
    NSGraphicsContext.saveGraphicsState()
    NSGraphicsContext.current = graphics

    let titleStyle = NSMutableParagraphStyle()
    titleStyle.lineBreakMode = .byWordWrapping
    let titleAttributes: [NSAttributedString.Key: Any] = [
        .font: NSFont.systemFont(ofSize: 54, weight: .bold),
        .foregroundColor: NSColor.white,
        .paragraphStyle: titleStyle,
    ]
    NSAttributedString(string: slide.title, attributes: titleAttributes)
        .draw(in: CGRect(x: 70, y: height - 205, width: width - 140, height: 100))

    let bulletStyle = NSMutableParagraphStyle()
    bulletStyle.lineSpacing = 10
    bulletStyle.paragraphSpacing = 18
    bulletStyle.firstLineHeadIndent = 0
    bulletStyle.headIndent = 34
    let bulletAttributes: [NSAttributedString.Key: Any] = [
        .font: NSFont.systemFont(ofSize: 35, weight: .regular),
        .foregroundColor: NSColor(calibratedWhite: 0.94, alpha: 1),
        .paragraphStyle: bulletStyle,
    ]
    let bulletText = slide.bullets.map { "•  \($0)" }.joined(separator: "\n")
    NSAttributedString(string: bulletText, attributes: bulletAttributes)
        .draw(in: CGRect(x: 92, y: 150, width: width - 184, height: 350))

    let footerAttributes: [NSAttributedString.Key: Any] = [
        .font: NSFont.monospacedSystemFont(ofSize: 20, weight: .medium),
        .foregroundColor: NSColor(calibratedWhite: 0.7, alpha: 1),
    ]
    NSAttributedString(string: "USACO Guide Easy C++ Solutions", attributes: footerAttributes)
        .draw(at: CGPoint(x: 70, y: 48))
    let counter = "\(number) / \(total)"
    let counterSize = counter.size(withAttributes: footerAttributes)
    NSAttributedString(string: counter, attributes: footerAttributes)
        .draw(at: CGPoint(x: CGFloat(width) - 70 - counterSize.width, y: 48))

    NSGraphicsContext.restoreGraphicsState()
}

for frame in 0..<frameCount {
    while !writerInput.isReadyForMoreMediaData {
        Thread.sleep(forTimeInterval: 0.005)
    }
    var optionalBuffer: CVPixelBuffer?
    guard CVPixelBufferPoolCreatePixelBuffer(nil, pool, &optionalBuffer) == kCVReturnSuccess,
          let buffer = optionalBuffer else {
        fail("could not allocate a video frame")
    }
    let second = Double(frame) / Double(fps)
    let slideIndex = min(slides.count - 1, Int(second / audioDuration * Double(slides.count)))
    draw(slides[slideIndex], number: slideIndex + 1, total: slides.count, into: buffer)
    let presentationTime = CMTime(value: Int64(frame), timescale: fps)
    guard adaptor.append(buffer, withPresentationTime: presentationTime) else {
        fail("could not append video frame: \(writer.error?.localizedDescription ?? "unknown")")
    }
}

writerInput.markAsFinished()
let writeSemaphore = DispatchSemaphore(value: 0)
writer.finishWriting { writeSemaphore.signal() }
writeSemaphore.wait()
guard writer.status == .completed else {
    fail("video encoding failed: \(writer.error?.localizedDescription ?? "unknown")")
}

let composition = AVMutableComposition()
let videoAsset = AVURLAsset(url: temporaryVideoURL)
guard let sourceVideo = videoAsset.tracks(withMediaType: .video).first,
      let destinationVideo = composition.addMutableTrack(withMediaType: .video, preferredTrackID: kCMPersistentTrackID_Invalid) else {
    fail("could not prepare the slide video track")
}
do {
    try destinationVideo.insertTimeRange(CMTimeRange(start: .zero, duration: videoAsset.duration), of: sourceVideo, at: .zero)
} catch {
    fail("could not insert the slide video: \(error)")
}

guard let sourceAudio = audioAsset.tracks(withMediaType: .audio).first,
      let destinationAudio = composition.addMutableTrack(withMediaType: .audio, preferredTrackID: kCMPersistentTrackID_Invalid) else {
    fail("could not prepare the narration track")
}
do {
    try destinationAudio.insertTimeRange(CMTimeRange(start: .zero, duration: audioAsset.duration), of: sourceAudio, at: .zero)
} catch {
    fail("could not insert narration: \(error)")
}

guard let exporter = AVAssetExportSession(asset: composition, presetName: AVAssetExportPresetHighestQuality) else {
    fail("could not create the final exporter")
}
exporter.outputURL = outputURL
exporter.outputFileType = .mp4
exporter.shouldOptimizeForNetworkUse = true
let exportSemaphore = DispatchSemaphore(value: 0)
exporter.exportAsynchronously { exportSemaphore.signal() }
exportSemaphore.wait()
guard exporter.status == .completed else {
    fail("final export failed: \(exporter.error?.localizedDescription ?? "unknown")")
}

try? manager.removeItem(at: temporaryVideoURL)
print("rendered \(outputURL.path) (\(String(format: "%.1f", audioDuration)) seconds)")
