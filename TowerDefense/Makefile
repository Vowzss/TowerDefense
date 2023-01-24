PROGRAM=TowerDefense

# Add your objs to generate in OBJS var
LEVELEDITOR=Sources/levelEditor/levelEditor.o Sources/levelEditor/grid.o
GAMESCENES=Sources/gameScenes/gameSelector.o Sources/gameScenes/game.o Sources/gameScenes/gameHowToPlay.o Sources/gameScenes/gameCredits.o Sources/gameScenes/gameWinner.o Sources/gameScenes/gameOver.o Sources/gameScenes/menu.o
GAMEMANAGER=Sources/gameManager/gameTowers.o Sources/gameManager/gameEnemies.o Sources/gameManager/gamePlayer.o Sources/gameManager/gameTextures.o Sources/gameManager/gameSounds.o Sources/gameManager/gameWaves.o Sources/gameManager/gameTowerManager.o 
SYSTEM=Sources/System/gameAnimator.o Sources/System/scene.o Sources/System/UIElement.o

OBJS=Sources/main.o $(GAMESCENES) $(LEVELEDITOR) $(GAMEMANAGER) $(SYSTEM)


CXX?=g++
TARGET?=$(shell $(CXX) -dumpmachine)

OPTIM_FLAGS?=-O0
CXXFLAGS=$(OPTIM_FLAGS) -g -Wall -Wextra -Wno-unused-parameter
CPPFLAGS=-IIncludes -IExternals/Includes -MMD
LDFLAGS=-LExternals/libs-$(TARGET)
LDLIBS=-lraylib

ifeq ($(TARGET),x86_64-linux-gnu)
LDLIBS+=-ldl -lpthread -lm
else ifeq ($(TARGET),x86_64-pc-cygwin)
LDLIBS+=-lgdi32
else ifeq ($(TARGET),wasm32-unknown-emscripten)
OPTIM_FLAGS=-Os
LDFLAGS+=-s ASYNCIFY
LDFLAGS+=-s USE_GLFW=3
LDFLAGS+=--preload-file Resources
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

build.tar.gz: $(PROGRAM) $(wildcard Resources/*)
	tar czf build.tar.gz $(PROGRAM) assets

host: $(PROGRAM)$(EXT)
	python3 -m http.server 8000

clean:
	rm -f $(OBJS) $(DEPS) $(PROGRAM) build.tar.gz
	rm -f $(PROGRAM).html $(PROGRAM).js $(PROGRAM).data $(PROGRAM).wasm