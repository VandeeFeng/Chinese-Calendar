# 🏮 中国传统农历黄历

一个用 C 语言编写的终端中国风农历黄历。

为了测试和完善在 opencode 里新的 agent 和 skill，纯 vibe。

![Chinese-Calendar.png](Chinese-Calendar.png)

## ✨ 特性

- 📅 **农历公历互转** - 准确的农历转换，支持闰月
- 📖 **传统黄历** - 宜忌、冲煞、吉凶神位一应俱全
- 👹 **动画神仙头像** - 土地公、财神、灶王爷等，支持动画效果
- 🎯 **交互式操作** - 键盘导航，流畅操作
- 🔮 **易经算命** - 内置简单的算命功能
- 📝 **日历视图** - 可切换的日历显示模式

## 🚀 快速开始

```bash
make
```

```bash
./chinese-calendar
```

## 📁 项目结构

```
Chinese-Calendar/
├── src/
│   ├── calendar/     # 农历计算
│   ├── almanac/      # 黄历计算
│   ├── ui/           # 用户界面
│   │   ├── layout/   # 布局管理
│   │   ├── components/ # UI 组件
│   │   └── visual/   # 视觉元素（神仙头像、大数字等）
│   ├── ncurses/      # ncurses 封装
│   └── utils/        # 工具函数
├── tests/            # 测试文件
└── Makefile          # 构建配置
```

