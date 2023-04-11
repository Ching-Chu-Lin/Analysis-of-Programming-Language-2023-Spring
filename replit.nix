{ pkgs }: {
	deps = [
		pkgs.adoptopenjdk-openj9-bin-16
  pkgs.clang_12
		pkgs.ccls
		pkgs.gdb
		pkgs.gnumake
	];
}