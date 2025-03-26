# Makefile

PYTHON = python
SCRIPT = weekly_summary_graph.py
DIST_DIR = dist
BUILD_DIR = build
SPEC_FILE = $(SCRIPT:.py=.spec)

# デフォルトターゲット（ビルド）
all: build

# ビルドターゲット
build:
	$(PYTHON) -m PyInstaller --onefile $(SCRIPT)

# 実行ターゲット
run:
	./$(DIST_DIR)/$(basename $(SCRIPT))

# クリーンアップターゲット
clean:
	rm -rf $(DIST_DIR) $(BUILD_DIR) __pycache__ $(SPEC_FILE)

# 再ビルドターゲット
rebuild: clean build

# ヘルプ
help:
	@echo "Usage:"
	@echo "  make build     - Build the executable using PyInstaller"
	@echo "  make run       - Run the generated executable"
	@echo "  make clean     - Remove build artifacts"
	@echo "  make rebuild   - Clean and rebuild the executable"
