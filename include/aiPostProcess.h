/*
Free Asset Import Library (ASSIMP)
----------------------------------------------------------------------

Copyright (c) 2006-2008, ASSIMP Development Team
All rights reserved.

Redistribution and use of this software in source and binary forms, 
with or without modification, are permitted provided that the 
following conditions are met:

* Redistributions of source code must retain the above
  copyright notice, this list of conditions and the
  following disclaimer.

* Redistributions in binary form must reproduce the above
  copyright notice, this list of conditions and the
  following disclaimer in the documentation and/or other
  materials provided with the distribution.

* Neither the name of the ASSIMP team, nor the names of its
  contributors may be used to endorse or promote products
  derived from this software without specific prior
  written permission of the ASSIMP Development Team.

THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS 
"AS IS" AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT 
LIMITED TO, THE IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR
A PARTICULAR PURPOSE ARE DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT 
OWNER OR CONTRIBUTORS BE LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL,
SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT 
LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES; LOSS OF USE,
DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON ANY 
THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT 
(INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE 
OF THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.

----------------------------------------------------------------------
*/

/** @file Definitions for import post processing steps */
#ifndef AI_POSTPROCESS_H_INC
#define AI_POSTPROCESS_H_INC

#include "aiTypes.h"

#ifdef __cplusplus
extern "C" {
#endif

/** Defines the flags for all possible post processing steps. */
enum aiPostProcessSteps
{
	/** Calculates the tangents and bitangents for the imported meshes. Does nothing
	 * if a mesh does not have normals. You might want this post processing step to be
	 * executed if you plan to use tangent space calculations such as normal mapping 
	 * applied to the meshes.
	 */
	aiProcess_CalcTangentSpace = 1,

	/** Identifies and joins identical vertex data sets within all imported meshes. 
	 * After this step is run each mesh does contain only unique vertices anymore,
	 * so a vertex is possibly used by multiple faces. You propably always want
	 * to use this post processing step.*/
	aiProcess_JoinIdenticalVertices = 2,

	/** Converts all the imported data to a left-handed coordinate space such as 
	 * the DirectX coordinate system. By default the data is returned in a right-handed
	 * coordinate space which for example OpenGL prefers. In this space, +X points to the
	 * right, +Y points towards the viewer and and +Z points upwards. In the DirectX 
   * coordinate space +X points to the right, +Y points upwards and +Z points 
   * away from the viewer.
	 */
	aiProcess_ConvertToLeftHanded = 4,

	/** Triangulates all faces of all meshes. By default the imported mesh data might 
	 * contain faces with more than 3 indices. For rendering a mesh you usually need
	 * all faces to be triangles. This post processing step splits up all higher faces
	 * to triangles.
	 */
	aiProcess_Triangulate = 8,

	/** Omits all normals found in the file. This can be used together
	 * with either the aiProcess_GenNormals or the aiProcess_GenSmoothNormals
	 * flag to force the recomputation of the normals.
	 */
	aiProcess_KillNormals = 0x10,

	/** Generates normals for all faces of all meshes. The normals are shared
	* between the three vertices of a face. This is ignored
	* if normals are already existing. This flag may not be specified together
	* with aiProcess_GenSmoothNormals
	*/
	aiProcess_GenNormals = 0x20,

	/** Generates smooth normals for all vertices in the mesh. This is ignored
	* if normals are already existing. This flag may not be specified together
	* with aiProcess_GenNormals
	*/
	aiProcess_GenSmoothNormals = 0x40,

	/** Splits large meshes into submeshes
	* This is quite useful for realtime rendering where the number of vertices
	* is usually limited by the video driver.
	*
	* The split limits can be set through aiSetVertexSplitLimit() and
	* aiSetTriangleSplitLimit(). The default values for this are defined
	* in the internal SplitLargeMeshes.h header as AI_SLM_DEFAULT_MAX_VERTICES
	* and AI_SLM_DEFAULT_MAX_TRIANGLES. 
	*/
	aiProcess_SplitLargeMeshes = 0x80
};

// ---------------------------------------------------------------------------
/** \brief Set the maximum number of vertices in a mesh.
 *
 * This is used by the SplitLargeMeshes PostProcess-Step to determine
 * whether a mesh must be splitted or not.
 * \param pLimit Vertex limit. 
 * \note The default value is AI_SLM_DEFAULT_MAX_VERTICES, defined in
 *       the internal header file SplitLargeMeshes.h
 */
aiReturn aiSetVertexSplitLimit(unsigned int pLimit);


// ---------------------------------------------------------------------------
/** \brief Set the maximum number of triangles in a mesh.
 *
 * This is used by the SplitLargeMeshes PostProcess-Step to determine
 * whether a mesh must be splitted or not.
 * \param pLimit Triangle limit
 * \note The default value is AI_SLM_DEFAULT_MAX_TRIANGLES, defined in
 *       the internal header file SplitLargeMeshes.h
 */
aiReturn aiSetTriangleSplitLimit(unsigned int pLimit);

#ifdef __cplusplus
} // end of extern "C"
#endif

#endif // AI_POSTPROCESS_H_INC
