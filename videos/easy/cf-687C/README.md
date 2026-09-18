# The Values You Can Make video package

- Proposed title: **The Values You Can Make: A Subset Inside a Subset | CF 687C C++**
- Narration voice: Daniel (macOS male system voice), aimed at grade 9
- Rendered video: [video.mp4](video.mp4)
- Narration audio: [narration.aiff](narration.aiff)
- Script: [narration.txt](narration.txt)
- Storyboard: [storyboard.md](storyboard.md)
- Algorithm: [algorithm.md](algorithm.md)
- Test walkthroughs: [test-cases.md](test-cases.md)
- Edge checklist: [edge-cases.md](edge-cases.md)
- Coding walkthrough: [coding-walkthrough.md](coding-walkthrough.md)
- Official problem: [The Values You Can Make](https://codeforces.com/contest/687/problem/C)
- GitHub solution: [cf-687C.cpp](https://github.com/hskark2024/usaco-guide-very-easy-solutions/blob/main/solutions/cf-687C.cpp)
- YouTube status: upload-ready; awaiting confirmation of channel, playlist creation, Private visibility, and Not made for kids audience before upload

## Proposed YouTube description

Solve Codeforces 687C with a two-dimensional subset-sum state compressed into bitsets. We derive the three choices for each coin, visualize payment and inside sums, explain descending rows, trace samples, and code an efficient C++17 solution.

Official problem: https://codeforces.com/contest/687/problem/C

GitHub solution: https://github.com/hskark2024/usaco-guide-very-easy-solutions/blob/main/solutions/cf-687C.cpp

Playlist: USACO Guide Easy C++ Solutions

#dynamicprogramming #knapsack #competitiveprogramming #cplusplus

## Local rendering

```sh
say -v Daniel -r 155 -f videos/easy/cf-687C/narration.txt -o videos/easy/cf-687C/narration.aiff
swift tools/render_easy_video.swift videos/easy/cf-687C/slides.tsv videos/easy/cf-687C/narration.aiff videos/easy/cf-687C/video.mp4
```
