# LeetCode Solutions

> 我的 LeetCode 刷题笔记：**中文题解 + C++ 代码**，全部题解整理在 [`solutions/`](./solutions) 目录下，按题号命名、按难度与算法建索引，持续更新。

<p align="center">
  <img src="./assets/readme/hero.svg" width="100%" alt="LeetCode Solutions 刷题记录：中文题解与 C++ 代码，按题号整理，每题一个目录">
</p>

> 想按 **难度 / 算法** 筛选或直接搜题号跳转？双击打开 [`index.html`](./index.html)（带搜索框和筛选按钮的本地索引页）。

<!-- leetcode-index:start -->

## 题目概览

共 **20** 道题 · Easy 6 · Medium 12 · Hard 2

**算法分布**：Array 9 · Math 9 · Dynamic Programming 5 · String 4 · Hash Table 3 · Geometry 2 · Matrix 2 · Sliding Window 2 · BFS 1 · Binary Search 1 · Binary Tree 1 · Bit Manipulation 1 等 21 个标签（全量见完整索引）

- 📖 **[完整索引](solutions/README.md)**：按题号 / 按难度 / 按算法三个视图，页首可锚点跳转
- 🔍 **[筛选页](index.html)**：搜题号与标题，按难度、算法筛选（本地双击打开）
- 🌐 **[在线筛选页](https://neneenen06.github.io/my-leetcode/)**：GitHub Pages 上直接筛难度 / 算法，点题号进题解

<!-- leetcode-index:end -->

## 这是什么

这是一份面向面试与个人复习的 LeetCode 刷题记录。每道题都写成独立的 Markdown 题解：中文思路、复杂度分析，以及可直接运行的 C++ 代码，而不是只粘贴一个通过答案。

## 如何浏览

所有题解统一放在 `solutions/` 目录下，每个题目一个目录，目录名 = **四位题号 + kebab-case 标题**，例如 `solutions/3875-construct-uniform-parity-array-i/`。

三种找题方式：

- **翻索引（GitHub 上就用这个）** —— [`solutions/README.md`](./solutions/README.md)：页首「快速跳转」列出全部难度与算法分组，点一下直接跳到对应分组；下面依次是**按题号**（题号可点进题解）、**按难度**、**按算法**。找某道题用浏览器 `Ctrl+F` 搜题号（如 `0835`）最快。
- **筛选 + 搜索（本地增强）** —— 打开 [`index.html`](./index.html)：本地双击即可，按难度和算法标签筛选，或输入题号 / 标题 / 标签实时过滤。GitHub 不渲染 HTML 文件，所以这一页只适合本地 / 桌面端用。
- **直接搜题号** —— 在仓库里搜 `0835`，直接落在 `solutions/0835-image-overlap/`。

每个题目目录的结构如下：

```text
solutions/
└── 3875-construct-uniform-parity-array-i/
    ├── README.md     # 中文题解：题意、思路、复杂度、C++ 代码
    └── solution.cpp  # 可直接编译运行的 C++ 实现
```

## 约定

- 题解目录一律放在 `solutions/` 下；根目录只保留本页（概览）、`assets/`、`index.html`（筛选页），题目明细不铺在根 README 里。
- 根 README 的概览、[`solutions/README.md`](./solutions/README.md) 的三个索引视图、`index.html` 都由 `scripts/generate_index.py` 从每题 README 的元信息行自动生成；请保留 `<!-- leetcode-index:start -->` 与 `<!-- leetcode-index:end -->` 标记，否则内容会被覆盖。
- 每题 README 的 `Difficulty` / `Topics` / `题目链接` 三行是索引的数据来源，新增题目时不要省。
- 所有题解默认使用 **C++17**。
- 仅供个人学习与复习使用。
