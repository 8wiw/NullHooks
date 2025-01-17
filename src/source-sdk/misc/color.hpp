#pragma once
#include <cstdint>
#include <d3d9.h>

/*
 * Thank you designer :
 *   https://www.unknowncheats.me/forum/counterstrike-global-offensive/385547-printing-console.html
 */
struct valve_color_t {
	unsigned char r;
	unsigned char g;
	unsigned char b;
	unsigned char a;
};

struct color {
	int a, r, g, b;
	color( ) = default;
	color( const int r, const int g, const int b, const int a = 255 ) {
		this->r = r;
		this->g = g;
		this->b = b;
		this->a = a;
	}

	explicit color( const uint32_t color ) {
		this->a = ( color >> 24 ) & 0xff;
		this->r = ( color >> 16 ) & 0xff;
		this->g = ( color >> 8 ) & 0xff;
		this->b = ( color & 0xff );
	}

	static color from_uint( const uint32_t uint ) {
		return color( uint );
	}

	// Returns the same color but with custom alpha. Used to do the color picker alpha fade.
	color get_custom_alpha(const int alpha) {
		return color{this->r, this->g, this->b, alpha};
	}

	static D3DCOLOR from_color( const color col ) {
		return D3DCOLOR_ARGB( col.a, col.r, col.g, col.b );
	}
	
	// For comparing colors
	bool operator != (color other) {
		return (other.r == r && other.g == g && other.b == b && other.a == a);
	}

	static color black( const int a = 255 ) { return { 0, 0, 0, a }; }
	static color white( const int a = 255 ) { return { 255, 255, 255, a }; }
	static color red( const int   a = 255 ) { return { 255, 0, 0, a }; }
	static color green( const int a = 255 ) { return { 0, 255, 0, a }; }
	static color blue( const int  a = 255 ) { return { 0, 0, 255, a }; }
};
