//
//  ofxFontStash.h
//  fontsExample
//
//  Created by Oriol Ferrer Mesià on 22/05/12.
//  Copyright (c) 2012 uri.cat. All rights reserved.
//

/*
 
 The MIT License
 
 Copyright (c) 2012, Oriol Ferrer Mesià.
 
 Permission is hereby granted, free of charge, to any person obtaining a copy
 of this software and associated documentation files (the "Software"), to deal
 in the Software without restriction, including without limitation the rights
 to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
 copies of the Software, and to permit persons to whom the Software is
 furnished to do so, subject to the following conditions:
 
 The above copyright notice and this permission notice shall be included in
 all copies or substantial portions of the Software.
 
 THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
 IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
 FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
 AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
 LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
 OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN
 THE SOFTWARE.
 */


#ifndef ofxFontStash_h
#define ofxFontStash_h


#include "ofMain.h"

// use the freetype libs to enabled .otf and .ttf fonts.
// if only .ttf required, stick with stb lib - look slightly better.
//#define FONS_USE_FREETYPE

// toggle this if we want to use the ofxUnicode dependency
//#define REQUIRES_OFX_UNICODE

#ifdef REQUIRES_OFX_UNICODE
#include "ofUTF8.h"
#include "ofTextConverter.h"
#endif

extern "C" {
#include "fontstash.h"
//#include <GLFW/glfw3.h> // Or any other GL header of your choice.
#include "glfontstash.h"
}

#define OFX_FONT_STASH_LINE_HEIGHT_MULT	0.8
#define FS_FONT_REGULAR 0
#define FS_FONT_ITALIC 1
#define FS_FONT_BOLD 2

class ofxFontStash{

	public:
		
		ofxFontStash();
		~ofxFontStash();
	
		//call this to set your font file (.ttf, etc)
		bool setup( string fontFile, float lineHeightPercent = 1.0f, int textureDimension = 512);

		//will draw text in one line, ignoring "\n"'s
        // added alignment as last parameter- accepts FONS_ALIGN_LEFT, FONS_ALIGN_CENTER, FONS_ALIGN_RIGHT
		void draw( string text, float size, float x, float y, int align = FONS_ALIGN_LEFT);

		//text with "\n" will produce line breaks
		void drawMultiLine( string text, float fontSize, float x, float y, int align = FONS_ALIGN_LEFT);
    
        // without unicode dependancy
        ofRectangle drawMultiLineColumn(string &text, float fontSize, float x, float y, float columnWidth);
    
        // break up the string with new lines at maxWidth (for replacement of drawMultiLineColumn)
        // and to be used with drawMultiLine()
        string wrapString(string text, float size, int maxWidth);

    #ifdef REQUIRES_OFX_UNICODE
		//fits text in a column of a certain width
		//if you only want to find out the bbox size, send in dontDraw=true
		//numLines will return the number of lines this has been split in
		ofRectangle drawMultiLineColumn( string &text, float fontSize, float x, float y,
											float columnWidth, int &numLines, bool dontDraw = false,
											int maxLines = 0, bool giveBackNewLinedText = false,
											bool * wordsWereTruncated = NULL );
    
        //fill in a string
        string walkAndFill(ofUTF8Ptr being, ofUTF8Ptr & iter, ofUTF8Ptr end);
    #endif

		//if the text has newlines, it will be treated as if was called into drawMultiLine()
		ofRectangle getBBox( string text, float size, float x, float y );
		ofRectangle getBBox( string text, float size, float x, float y, float columnWidth );

        // new
        bool addFontVarient(string fontFile, int varient);

		//interleave drawBatch* calls between begin() and end()
		//void beginBatch();
		//void drawBatch( string text, float size, float x, float y);
		//void drawMultiLineBatch( string text, float size, float x, float y );
		//void endBatch();

		void setLineHeight(float percent);
        void setColor(ofColor color);
	
private:
		
		float				lineHeight; // as percent, 1.0 would be normal
		//struct sth_stash*	stash;
        struct FONScontext* stash;

        int					regularFontID;
        int					italicFontID;
        int					boldFontID;


        //bool				batchDrawing;
        unsigned int        color;

};


#endif
