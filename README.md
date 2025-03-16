# MyHabitsTracker Ver.01

MyHabitsTrackerは、習慣の達成状況を記録し可視化できるCLIアプリです。 

## 特徴

- 習慣の自由な追加・編集・削除
- 習慣の達成状況を毎日記録
- 今日・1週間・1か月・すべての期間の記録を可視化
- 英語・日本語の両方に対応
- 記録と習慣リストのデータはJSON形式で保存
- 軽量&シンプルなCLI

## 今後のアップデート予定

- 達成状況の CSV 出力機能
- 達成状況のグラフ化

## 使い方

### インストール
```
git clone https://github.com/chiaki-ari/MyHabitsTracker.git
cd MyHabitsTracker
mingw32-make
```
または、リリースから直接ダウンロードすることもできます。

### 実行
```
./tracker.exe
```

### 操作方法
```
==== 習慣達成表 ver.1 ====
[0] 記録更新
[1] 記録表示
[2] 習慣管理
[x] 終了/戻る
```
選択肢の番号を入力します。

### 記録の管理

- 習慣を追加する → [2] 習慣リストを編集する
- 今日の達成状況を記録 → [0] 記録を追加する
- 過去の達成状況を確認 → [1] 記録を表示する

### 言語の選択

アプリ起動時に言語を選択できます。（e = English / j = 日本語）
```
Please select a language (e: English, j: Japanese)
言語を選択してください (e: 英語, j: 日本語)
> 
```

## データの保存形式

習慣リストと記録はJSONファイルで保存されます。

- data/habits.json（習慣リスト）
- data/records.json（記録データ）

---

# MyHabitsTracker Ver.01

MyHabitsTracker is a CLI application that records and visualizes habit achievement.

## Features

- Freely add, edit, and delete habits
- Record habit achievements daily
- Visualize records for today, one week, one month, and all periods
- Supports both English and Japanese
- Data is saved in JSON format
- Lightweight & Simple CLI

## Future Updates

- CSV export of achievement data
- Graphical visualization of achievements

## Usage

### Installation
```
git clone https://github.com/chiaki-ari/MyHabitsTracker.git
cd MyHabitsTracker
mingw32-make
```
Alternatively, you can download the executable directly from Releases.

### Execution
./tracker.exe

### Operation
```
==== Habit Achievement Table ver.1 ==== 
[0] Update Records
[1] View Records
[2] Manage Habits
[x] Exit/Back
```
Enter the number of your choice.

### Record Management

- Add habits → [2] Edit Habit List
- Record today's achievements → [0] Add Records
- Check past achievements → [1] Show Records

### Language Selection

Select a language when the app starts. (e = English / j = Japanese)

```
Please select a language (e: English, j: Japanese)
言語を選択してください (e: 英語, j: 日本語)
> 
```

## Data Storage Format

Habit lists and records are saved in JSON files.

- data/habits.json (Habit List)
- data/records.json (Record Data)

