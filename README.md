# MyHabitsTracker Ver.01

MyHabitsTrackerは、習慣の達成状況を記録し可視化できるCLIアプリです。 

## 特徴

- 習慣の自由な追加・編集・削除
- 習慣の達成状況を毎日記録
- 今日・1週間・1か月・すべての期間の記録を可視化
- 英語・日本語の両方に対応
- 記録と習慣リストのデータはJSON形式で保存
- 軽量&シンプルなCLI

**新機能**
- **連続記録モード**: 開始日と終了日を指定し、選択した全習慣または単一習慣をまとめて連続記録できます。
- **ページング機能**: 記録表示時に ← / → キーで前日・翌日、前週・翌週、前月・翌月へ素早く移動
- **ユーザー切り替え**: ユーザーごとに別フォルダに習慣/記録データを保存

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
[0] 記録を更新
[1] 記録を見る
[2] 習慣を管理
[x] 終了/戻る
```
選択肢の番号を入力してEnterを押します。

**記録表示時のページング**
- 日表示モード→前日・翌日
- 週表示モード→前週・翌週
- 月表示モード→前月・翌月

**連続記録モード**
- 全習慣連続記録: 開始日から終了日まで、登録済みの習慣を一括して連続記録
- 単一習慣連続記録: 開始日から終了日まで、特定の習慣を連続記録

### 記録の管理

- 習慣を追加・変更したい → [2] 
- 達成状況を記録したい → [0]
- 過去の達成状況を確認したい → [1] 

### ユーザー切り替え

- アプリ起動後、言語を選択したあとユーザーIDを指定可能です。
- 指定したユーザーごとに専用フォルダが作成され、以下のようにデータを保存します。
```
data/<ユーザー名>/habits.json
data/<ユーザー名>/records.json
data/<ユーザー名>/weekly_summary.json
```
- ユーザーを変えると、まったく別の習慣一覧・記録を管理できます。

### 言語の選択

アプリ起動時に言語を選択できます。（e = English / j = 日本語）
```
Please select a language (e: English, j: Japanese)
言語を選択してください (e: 英語, j: 日本語)
> 
```

### Windowsでの文字化け回避

1. コマンドプロンプトまたはPowerShellで以下を実行:
```
chcp 65001
```
2. コンソールのフォントを **MS ゴシック** にすると日本語が正しく表示されやすいです。
3. それでもうまくいかない場合は、Shift-JISで実行しつつ日本語入力を行うなど別途対策を検討してください。

## データの保存形式

習慣リストと記録はJSONファイルで保存されます。

- data/<ユーザー名>/habits.json（習慣リスト）
- data/<ユーザー名>/records.json（記録データ）
- data/<ユーザー名>/weekly_summary.json（週計記録データ）

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

**New**
- **Continuous Recording Mode**: Record all habits or a single habit continuously from a start date to an end date.
- **Paging**: Use ← / → keys to move to previous/next day (or week/month) when viewing records
- **User Switching**: Each user gets a separate folder and data (habits/records/weekly summary)


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

**Paging Navigation:**
- Day view → previous/next day (← / →)
- Week view → previous/next week
- Month view → previous/next month

**Continuous Recording:**
- **By date**: Record all habits continuously from start date to end date
- **By habit**: Record a single habit repeatedly between the chosen dates


### Record Management

- Add habits → [2] Edit Habit List
- Record today's achievements → [0] Add Records
- Check past achievements → [1] Show Records

### User Switching

- After language selection, you can specify a user ID
- The data folder will be created under `data/<UserName>/`
```
data/<UserName>/habits.json
data/<UserName>/records.json
data/<UserName>/weekly_summary.json
```
- This allows completely separate sets of habits and records per user.


### Language Selection

Select a language when the app starts. (e = English / j = Japanese)

```
Please select a language (e: English, j: Japanese)
言語を選択してください (e: 英語, j: 日本語)
> 
```

### Windows Code Page Notes

1. Run `chcp 65001` in Command Prompt or PowerShell to set the console code page to UTF-8.
2. Set the console font to **MS Gothic** for proper Japanese rendering.
3. If the text is still garbled, consider running the application under Shift-JIS code page or using Windows Terminal with UTF-8 support.


## Data Storage Format

Habit lists and records are saved in JSON files.

- data/<UserName>/habits.json (Habit List)
- data/<UserName>/records.json (Record Data)
- data/<UserName>/weekly_summary.json (Weekly Summary)

