# Two Sets II video package

- Proposed title: **Two Sets II: Count Equal Partitions Without Double Counting | CSES 1093 C++**
- Narration voice: Daniel (macOS male system voice), aimed at grade 9
- Rendered video: [video.mp4](video.mp4)
- Narration audio: [narration.aiff](narration.aiff)
- Script: [narration.txt](narration.txt)
- Storyboard: [storyboard.md](storyboard.md)
- Algorithm: [algorithm.md](algorithm.md)
- Test walkthroughs: [test-cases.md](test-cases.md)
- Edge checklist: [edge-cases.md](edge-cases.md)
- Coding walkthrough: [coding-walkthrough.md](coding-walkthrough.md)
- Official problem: [Two Sets II](https://cses.fi/problemset/task/1093)
- GitHub solution: [cses-1093.cpp](https://github.com/hskark2024/usaco-guide-very-easy-solutions/blob/main/solutions/cses-1093.cpp)
- YouTube status: upload-ready; awaiting confirmation of channel, playlist creation, Private visibility, and Not made for kids audience before upload

## Proposed YouTube description

Learn exact-sum counting DP and a simple way to avoid counting each partition twice. We pin the largest number to one side, derive the recurrence, explain downward updates, trace N=3 and N=7, prove correctness, and implement C++17.

Official problem: https://cses.fi/problemset/task/1093

GitHub solution: https://github.com/hskark2024/usaco-guide-very-easy-solutions/blob/main/solutions/cses-1093.cpp

Playlist: USACO Guide Easy C++ Solutions

#dynamicprogramming #knapsack #competitiveprogramming #cplusplus

## Local rendering

```sh
say -v Daniel -r 155 -f videos/easy/cses-1093/narration.txt -o videos/easy/cses-1093/narration.aiff
swift tools/render_easy_video.swift videos/easy/cses-1093/slides.tsv videos/easy/cses-1093/narration.aiff videos/easy/cses-1093/video.mp4
```
