#pragma once

#define BEADNUM 15 * 15

// 棋盘位置索引
struct PlateIndex {
	int i;
	int j;
};

// 棋盘落子状态
enum PlateState {
	Empty = 0,
	Black = 1,
	White = 2,
};

// 棋子大小
enum BeadSize {
	Width = 60, 
	Height = 60,
};

// 棋盘可点击范围
enum PlateTouchRange {
	Left = 30,
	Right = 930,
	Bottom = 30,
	Top = 930,
};