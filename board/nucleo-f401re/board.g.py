module("genos.board", impl = "nucleo-f401re",
	sources = ["src/board.c"],
	include_paths = "include",
	mdepends = [
		("genos.hal", "stm32f401"),
	],
	defines=["BOARD_NUCLEO_F401RE"]
)