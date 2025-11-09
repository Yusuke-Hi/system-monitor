# Linux Resource Monitor

C++によるLinuxリソース監視システム

## 概要
Linuxシステムの/procファイルシステムを解析し、
CPU、メモリ、ディスクI/Oなどのリソース使用状況を
リアルタイムで監視・表示するツール。

## 開発の目的
- C++のスキル向上
- Linuxシステムプログラミングの学習
- リアルタイムデータ処理の実践

## 技術スタック
- 言語: C++14
- OS: Linux
- ビルド: CMake

## 現在の実装状況
- [x] /proc/statからCPU使用率を取得
- [x] /proc/meminfoからメモリ使用率を取得
- [x] ディスクI/O監視

## ビルド方法
```bash
mkdir build && cd build
cmake ..
make
./src/execute-system-monitor
```

## 今後の予定
- テスト作成
- CI作成
