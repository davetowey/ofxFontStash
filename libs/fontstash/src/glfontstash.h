//
// Copyright (c) 2009-2013 Mikko Mononen memon@inside.org
//
// This software is provided 'as-is', without any express or implied
// warranty.  In no event will the authors be held liable for any damages
// arising from the use of this software.
// Permission is granted to anyone to use this software for any purpose,
// including commercial applications, and to alter it and redistribute it
// freely, subject to the following restrictions:
// 1. The origin of this software must not be misrepresented; you must not
//    claim that you wrote the original software. If you use this software
//    in a product, an acknowledgment in the product documentation would be
//    appreciated but is not required.
// 2. Altered source versions must be plainly marked as such, and must not be
//    misrepresented as being the original software.
// 3. This notice may not be removed or altered from any source distribution.
//
#ifndef GLFONTSTASH_H
#define GLFONTSTASH_H

struct FONScontext* glfonsCreate(int width, int height, int flags);
void glfonsDelete(struct FONScontext* ctx);

unsigned int glfonsRGBA(unsigned char r, unsigned char g, unsigned char b, unsigned char a);

#endif

#ifdef GLFONTSTASH_IMPLEMENTATION

struct GLFONScontext {
	GLuint tex;
	int width, height;
#ifdef TARGET_PROGRAMMABLE_GL
    ofVboMesh* mesh;
#endif
};

static int glfons__renderCreate(void* userPtr, int width, int height)
{
	struct GLFONScontext* gl = (struct GLFONScontext*)userPtr;
	// Create may be called multiple times, delete existing texture.
	if (gl->tex != 0) {
		glDeleteTextures(1, &gl->tex);
		gl->tex = 0;
	}
	glGenTextures(1, &gl->tex);
	if (!gl->tex) return 0;
	gl->width = width;
	gl->height = height;
	glBindTexture(GL_TEXTURE_2D, gl->tex);
    
#ifdef TARGET_PROGRAMMABLE_GL
    
    if(gl->mesh != NULL){
        
        delete(gl->mesh);
        gl->mesh = NULL;
        
    }
    
    gl->mesh = new ofVboMesh();
    
    glTexImage2D(GL_TEXTURE_2D, 0, GL_RED, gl->width, gl->height, 0, GL_RGBA, GL_UNSIGNED_BYTE, 0);
    
#else
    glTexImage2D(GL_TEXTURE_2D, 0, GL_ALPHA, gl->width, gl->height, 0, GL_ALPHA, GL_UNSIGNED_BYTE, 0);
#endif

    
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	return 1;
}

static int glfons__renderResize(void* userPtr, int width, int height)
{
	// Reuse create to resize too.
	return glfons__renderCreate(userPtr, width, height);
}


static void glfons__renderUpdate(void* userPtr, int* rect, const unsigned char* data)
{
	struct GLFONScontext* gl = (struct GLFONScontext*)userPtr;
	int w = rect[2] - rect[0];
	int h = rect[3] - rect[1];

	if (gl->tex == 0) return;
    
    #ifdef TARGET_OPENGLES
    
    // http://stackoverflow.com/questions/205522/opengl-subtexturing/205569#205569
    // http://stackoverflow.com/questions/25424558/opengl-es-updating-a-sub-part-of-a-texture-without-using-glpixelstorei?lq=1
    // FIXME: this is a bit too slow
    glBindTexture(GL_TEXTURE_2D, gl->tex);
    glPixelStorei(GL_UNPACK_ALIGNMENT,1);
    //glTexSubImage2D(GL_TEXTURE_2D, 0, rect[0], rect[1], w, h, GL_ALPHA, GL_UNSIGNED_BYTE, data);
    
    int y = 0;
    for(y = 0; y < h; y++) {
        const unsigned char *row = data + ((y + rect[1])*gl->width + rect[0]);// * 4;
        glTexSubImage2D(GL_TEXTURE_2D, 0, rect[0], rect[1] + y, w, 1, GL_ALPHA, GL_UNSIGNED_BYTE, row);
    }
    
    #else
    
    #ifdef TARGET_PROGRAMMABLE_GL
    
    // http://stackoverflow.com/questions/205522/opengl-subtexturing/205569#205569
    // http://stackoverflow.com/questions/25424558/opengl-es-updating-a-sub-part-of-a-texture-without-using-glpixelstorei?lq=1
    // FIXME: this is a bit too slow
    glBindTexture(GL_TEXTURE_2D, gl->tex);
    glPixelStorei(GL_UNPACK_ALIGNMENT,1);
    //glTexSubImage2D(GL_TEXTURE_2D, 0, rect[0], rect[1], w, h, GL_ALPHA, GL_UNSIGNED_BYTE, data);
    
    int y = 0;
    for(y = 0; y < h; y++) {
        const unsigned char *row = data + ((y + rect[1])*gl->width + rect[0]);// * 4;
        glTexSubImage2D(GL_TEXTURE_2D, 0, rect[0], rect[1] + y, w, 1, GL_RED, GL_UNSIGNED_BYTE, row);
    }
    
    #else
    
    // this should work for glfw + glew
	glPushClientAttrib(GL_CLIENT_PIXEL_STORE_BIT);
	glBindTexture(GL_TEXTURE_2D, gl->tex);
	glPixelStorei(GL_UNPACK_ALIGNMENT,1);
	glPixelStorei(GL_UNPACK_ROW_LENGTH, gl->width);
	glPixelStorei(GL_UNPACK_SKIP_PIXELS, rect[0]);
	glPixelStorei(GL_UNPACK_SKIP_ROWS, rect[1]);
	glTexSubImage2D(GL_TEXTURE_2D, 0, rect[0], rect[1], w, h, GL_ALPHA,GL_UNSIGNED_BYTE, data);
	glPopClientAttrib();

    
    #endif
    #endif
}

void hextofloat(int c, float *f)
{
    
    
    f[3] = ((c >> 24) & 0xFF) / 255.0;  // Extract the RR byte
    f[2] = ((c >> 16) & 0xFF) / 255.0;   // Extract the GG byte
    f[1] = ((c >> 8) & 0xFF) / 255.0;        // Extract the BB byte
    f[0] = (c & 0xFF) / 255.0;        // Extract the BB byte
    
    
}

static void glfons__renderDraw(void* userPtr, const float* verts, const float* tcoords, const unsigned int* colors, int nverts)
{
    
#ifdef TARGET_PROGRAMMABLE_GL
    
    struct GLFONScontext* gl = (struct GLFONScontext*)userPtr;
    if (gl->tex == 0) return;
	
    gl->mesh->setMode(OF_PRIMITIVE_TRIANGLES);

    ofSetColor(255,255,255,255);
    gl->mesh->clear();
    
    for(int i = 0; i < nverts; i++){
        
        gl->mesh->addVertex(ofVec3f(verts[i*2], verts[i*2+1], 0));
        gl->mesh->addTexCoord(ofVec2f(tcoords[i*2],tcoords[i*2+1]));
        
        float f[4];
        hextofloat(colors[i], f);
        gl->mesh->addColor(ofFloatColor(f[0], f[1],f[2],f[3]));
        
        
    }
    
  
    glEnable(GL_TEXTURE_2D);
	glBindTexture(GL_TEXTURE_2D, gl->tex);
	
    gl->mesh->draw(OF_MESH_FILL);
    
    
    
	glDisable(GL_TEXTURE_2D);
    
#else
    
    struct GLFONScontext* gl = (struct GLFONScontext*)userPtr;
	if (gl->tex == 0) return;
	glBindTexture(GL_TEXTURE_2D, gl->tex);
	glEnable(GL_TEXTURE_2D);
	glEnableClientState(GL_VERTEX_ARRAY);
	glEnableClientState(GL_TEXTURE_COORD_ARRAY);
	glEnableClientState(GL_COLOR_ARRAY);
    
	glVertexPointer(2, GL_FLOAT, sizeof(float)*2, verts);
	glTexCoordPointer(2, GL_FLOAT, sizeof(float)*2, tcoords);
	glColorPointer(4, GL_UNSIGNED_BYTE, sizeof(unsigned int), colors);
    
	glDrawArrays(GL_TRIANGLES, 0, nverts);
    
	glDisable(GL_TEXTURE_2D);
	glDisableClientState(GL_VERTEX_ARRAY);
	glDisableClientState(GL_TEXTURE_COORD_ARRAY);
	glDisableClientState(GL_COLOR_ARRAY);
    
#endif
    
    
}

static void glfons__renderDelete(void* userPtr)
{
	struct GLFONScontext* gl = (struct GLFONScontext*)userPtr;
	if (gl->tex != 0)
		glDeleteTextures(1, &gl->tex);
	gl->tex = 0;
	free(gl);
}


struct FONScontext* glfonsCreate(int width, int height, int flags)
{
	struct FONSparams params;
	struct GLFONScontext* gl;

	gl = (struct GLFONScontext*)malloc(sizeof(struct GLFONScontext));
	if (gl == NULL) goto error;
	memset(gl, 0, sizeof(struct GLFONScontext));

	memset(&params, 0, sizeof(params));
	params.width = width;
	params.height = height;
	params.flags = (unsigned char)flags;
	params.renderCreate = glfons__renderCreate;
	params.renderResize = glfons__renderResize;
	params.renderUpdate = glfons__renderUpdate;
	params.renderDraw = glfons__renderDraw; 
	params.renderDelete = glfons__renderDelete;
	params.userPtr = gl;

	return fonsCreateInternal(&params);

error:
	if (gl != NULL) free(gl);
	return NULL;
}

void glfonsDelete(struct FONScontext* ctx)
{
	fonsDeleteInternal(ctx);
}

unsigned int glfonsRGBA(unsigned char r, unsigned char g, unsigned char b, unsigned char a)
{
	return (r) | (g << 8) | (b << 16) | (a << 24);
}

#endif
