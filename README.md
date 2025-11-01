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
- [o] /proc/statからCPU使用率を取得
- [o] /proc/meminfoからメモリ使用率を取得
- [ ] ディスクI/O監視
- [ ] プロセス一覧表示
- [ ] GUIフロントエンド

## ビルド方法
```bash
mkdir build && cd build
cmake ..
make
./src/execute-system-monitor
```

## 今後の予定
- ディスクI/O監視機能の追加
- プロセスごとのリソース使用状況表示
- ncursesを使ったTUI実装
- テスト作成
