SHELL       := zsh

SCRIPT_NAME := add_metadata
BIN_PATH    := ~/.local/bin/$(SCRIPT_NAME)

symlink     := install -v -l as

all: main workflow

main: main.sh.zwc dir
	$(symlink) $@.sh $(BIN_PATH)/$@
	$(symlink) $< $(BIN_PATH)/$@.zwc
	chmod +x $(BIN_PATH)/$@

workflow: workflow.workflow workflow.sh.zwc dir
	$(symlink) $@.$@ ~/Library/Workflows/Applications/Folder\ Actions/$(SCRIPT_NAME).$@

	$(symlink) $@.sh                   $(BIN_PATH)/$@.sh
	$(symlink) $@.sh.zwc               $(BIN_PATH)/$@.sh.zwc

%.sh.zwc: %.sh
	zcompile $<

dir:
	if   [[ -d $(BIN_PATH) ]]; then exit 0;\
	elif [[ -e $(BIN_PATH) ]]; then rm $(BIN_PATH);\
	fi;\
	mkdir $(BIN_PATH)
