PROGRAM=TowerDefense

# Add your objs to generate in OBJS var
LEVELEDITOR=src/levelEditor/levelEditor.o src/levelEditor/grid.o
GAMESCENES=src/gameScenes/gameSelector.o src/gameScenes/game.o src/gameScenes/gameHowToPlay.o src/gameScenes/gameCredits.o src/gameScenes/gameWinner.o src/gameScenes/gameOver.o src/gameScenes/menu.o
GAMEMANAGER=src/gameManager/gameTowers.o src/gameManager/gameEnemies.o src/gameManager/gamePlayer.o src/gameManager/gameTextures.o src/gameManager/gameSounds.o src/gameManager/gameWaves.o src/gameManager/gameTowerManager.o 
SYSTEM=src/System/gameAnimator.o src/System/scene.o src/System/UIElement.o

OBJS=src/main.o $(GAMESCENES) $(LEVELEDITOR) $(GAMEMANAGER) $(SYSTEM)


CXX?=g++
TARGET?=$(shell $(CXX) -dumpmachine)

OPTIM_FLAGS?=-O0
CXXFLAGS=$(OPTIM_FLAGS) -g -Wall -Wextra -Wno-unused-parameter
CPPFLAGS=-Iinclude -Ithird_party/include -MMD
LDFLAGS=-Lthird_party/libs-$(TARGET)
LDLIBS=-lraylib

ifeq ($(TARGET),x86_64-linux-gnu)
LDLIBS+=-ldl -lpthread -lm
else ifeq ($(TARGET),x86_64-pc-cygwin)
LDLIBS+=-lgdi32
else ifeq ($(TARGET),wasm32-unknown-emscripten)
OPTIM_FLAGS=-Os
LDFLAGS+=-s ASYNCIFY
LDFLAGS+=-s USE_GLFW=3
LDFLAGS+=--preload-file assets
EXT=.html
endif

DEPS=$(OBJS:.o=.d)

.PHONY: all clean

all: $(PROGRAM)$(EXT)

-include $(DEPS)

%.o: %.c
	$(CXX) -c $(CXXFLAGS) $(CPPFLAGS) $< -o $@

$(PROGRAM)$(EXT): $(OBJS)
	$(CXX) $(CXXFLAGS) $(CPPFLAGS) $(LDFLAGS) $^ $(LDLIBS) -o $@

build.tar.gz: $(PROGRAM) $(wildcard assets/*)
	tar czf build.tar.gz $(PROGRAM) assets

host: $(PROGRAM)$(EXT)
	python3 -m http.server 8000

clean:
	rm -f $(OBJS) $(DEPS) $(PROGRAM) build.tar.gz
	rm -f $(PROGRAM).html $(PROGRAM).js $(PROGRAM).data $(PROGRAM).wasm