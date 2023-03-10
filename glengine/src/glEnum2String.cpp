/*
 * PEM_GL - Copyright © 2022-2022 DAVID Axel
 * Mail to:
 * axel.david@etu.univ-amu.fr
 *
 * PEM_GL is free software: you can redistribute it and/or modify it under the terms of
 * the GNU General Public License as published by the Free Software Foundation,
 * either version 3 of the License, or (at your option) any later version.
 *
 * PEM_GL is distributed in the hope that it will be useful, but WITHOUT ANY WARRANTY;
 * without even the implied warranty of MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.
 * See the GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License along with this program.
 * If not, see <https://www.gnu.org/licenses/>.
 */

/*
 * PEX_GL - Copyright © 2022 DAVID Axel
 * Mail to:
 * axel.david@etu.univ-amu.fr
 *
 * PEX_GL is free software: you can redistribute it and/or modify it under the terms of
 * the GNU General Public License as published by the Free Software Foundation,
 * either version 3 of the License, or (at your option) any later version.
 *
 * PEX_GL is distributed in the hope that it will be useful, but WITHOUT ANY WARRANTY;
 * without even the implied warranty of MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.
 * See the GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License along with this program.
 * If not, see <https://www.gnu.org/licenses/>.
 */

/*
 * Bidon_OpenGL - Copyright © 2022 DAVID Axel, GOI Suzy
 * Mail to:
 * axel.david@etu.univ-amu.fr
 * muriel.coet@etu.univ-amu.fr
 *
 * Bidon_OpenGL is free software: you can redistribute it and/or modify it under the terms of
 * the GNU General Public License as published by the Free Software Foundation,
 * either version 3 of the License, or (at your option) any later version.
 *
 * Bidon_OpenGL is distributed in the hope that it will be useful, but WITHOUT ANY WARRANTY;
 * without even the implied warranty of MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.
 * See the GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License along with this program.
 * If not, see <https://www.gnu.org/licenses/>.
 */

#include <GLFW/glfw3.h>
#include <string>
#include <stdexcept>

#include <glengine/utility.hpp>

std::string gl_engine::utility::to_string( const GLenum macro ) {
    switch(macro) {
        case GL_FRAGMENT_SHADER : return "GL_FRAGMENT_SHADER";
        case GL_VERTEX_SHADER : return "GL_VERTEX_SHADER";
        case GL_GEOMETRY_SHADER : return "GL_GEOMETRY_SHADER";

        case GL_ARRAY_BUFFER : return "GL_ARRAY_BUFFER";
        case GL_ELEMENT_ARRAY_BUFFER : return "GL_ELEMENT_ARRAY_BUFFER";
        case GL_ARRAY_BUFFER_BINDING : return "GL_ARRAY_BUFFER_BINDING";

        case GL_STREAM_DRAW : return "GL_STREAM_DRAW";
        case GL_STREAM_READ : return "GL_STREAM_READ";
        case GL_STREAM_COPY : return "GL_STREAM_COPY";

        case GL_STATIC_DRAW : return "GL_STATIC_DRAW";
        case GL_STATIC_READ : return "GL_STATIC_READ";
        case GL_STATIC_COPY : return "GL_STATIC_COPY";

        case GL_DYNAMIC_DRAW : return "GL_DYNAMIC_DRAW";
        case GL_DYNAMIC_READ : return "GL_DYNAMIC_READ";
        case GL_DYNAMIC_COPY : return "GL_DYNAMIC_COPY";

            // GL_POINTS/GL_ZERO/GL_NONE/GL_NO_ERROR <=>
        case GL_FALSE : return "GL_FALSE/GL_POINTS/GL_ZERO/GL_NONE/GL_NO_ERROR";
            // GL_LINES/GL_ONE/GL_CURRENT_BIT/GL_CONTEXT_FLAG_FORWARD_COMPATIBLE_BIT <=>
            // GL_MAP_READ_BIT/GL_CONTEXT_CORE_PROFILE_BIT/GL_SYNC_FLUSH_COMMANDS_BIT <=>
        case GL_TRUE : return "GL_TRUE/GL_LINES/GL_ONE/GL_CURRENT_BIT/GL_CONTEXT_FLAG_FORWARD_COMPATIBLE_BIT/"
                              "GL_MAP_READ_BIT/GL_CONTEXT_CORE_PROFILE_BIT/GL_SYNC_FLUSH_COMMANDS_BIT";

            // GL_ACCUM <=>
        case GL_DEPTH_BUFFER_BIT : return "GL_DEPTH_BUFFER_BIT/GL_ACCUM";
            // GL_FRONT_LEFT <=>
        case GL_STENCIL_BUFFER_BIT : return "GL_STENCIL_BUFFER_BIT/GL_FRONT_LEFT";
            // GL_LIGHT0 <=>
        case GL_COLOR_BUFFER_BIT : return "GL_COLOR_BUFFER_BIT/GL_LIGHT0";

            // GL_POINT_BIT/GL_CLIENT_PIXEL_STORE_BIT/GL_CLIENT_VERTEX_ARRAY_BIT <=>
            // GL_MAP_WRITE_BIT/GL_CONTEXT_COMPATIBILITY_PROFILE_BIT <=>
        case GL_LINE_LOOP : return "GL_LINE_LOOP/GL_POINT_BIT/GL_CLIENT_PIXEL_STORE_BIT/GL_CLIENT_VERTEX_ARRAY_BIT/"
                                   "GL_MAP_WRITE_BIT/GL_CONTEXT_COMPATIBILITY_PROFILE_BIT";
        case GL_LINE_STRIP : return "GL_LINE_STRIP";
            // GL_LINE_BIT/GL_MAP_INVALIDATE_RANGE_BIT <=>
        case GL_TRIANGLES : return "GL_TRIANGLES/GL_LINE_BIT/GL_MAP_INVALIDATE_RANGE_BIT";
        case GL_TRIANGLE_STRIP : return "GL_TRIANGLE_STRIP";
        case GL_TRIANGLE_FAN : return "GL_TRIANGLE_FAN";
        case GL_QUADS : return "GL_QUADS";

            // GL_ACCUM_BUFFER_BIT <=>
        case GL_NEVER : return "GL_NEVER/GL_ACCUM_BUFFER_BIT";
        case GL_LESS : return "GL_LESS";
        case GL_EQUAL : return "GL_EQUAL";
        case GL_LEQUAL : return "GL_LEQUAL";
        case GL_GREATER : return "GL_GREATER";
        case GL_NOTEQUAL : return "GL_NOTEQUAL";
        case GL_GEQUAL : return "GL_GEQUAL";
        case GL_ALWAYS : return "GL_ALWAYS";

        case GL_SRC_COLOR : return "GL_SRC_COLOR";
        case GL_ONE_MINUS_SRC_COLOR : return "GL_ONE_MINUS_SRC_COLOR";

        case GL_SRC_ALPHA : return "GL_SRC_ALPHA";
        case GL_ONE_MINUS_SRC_ALPHA : return "GL_ONE_MINUS_SRC_ALPHA";
        case GL_DST_ALPHA : return "GL_DST_ALPHA";
        case GL_ONE_MINUS_DST_ALPHA : return "GL_ONE_MINUS_DST_ALPHA";

        case GL_DST_COLOR : return "GL_DST_COLOR";
        case GL_ONE_MINUS_DST_COLOR : return "GL_ONE_MINUS_DST_COLOR";

        case GL_SRC_ALPHA_SATURATE : return "GL_SRC_ALPHA_SATURATE";

        case GL_FRONT_RIGHT : return "GL_FRONT_RIGHT";
        case GL_BACK_LEFT : return "GL_BACK_LEFT";
        case GL_BACK_RIGHT : return "GL_BACK_RIGHT";
        case GL_FRONT : return "GL_FRONT";
        case GL_BACK : return "GL_BACK";
        case GL_LEFT : return "GL_LEFT";
        case GL_RIGHT : return "GL_RIGHT";
        case GL_FRONT_AND_BACK : return "GL_FRONT_AND_BACK";

        case GL_INVALID_ENUM : return "GL_INVALID_ENUM";
        case GL_INVALID_VALUE : return "GL_INVALID_VALUE";
        case GL_INVALID_OPERATION : return "GL_INVALID_OPERATION";
        case GL_OUT_OF_MEMORY : return "GL_OUT_OF_MEMORY";

        case GL_CW : return "GL_CW";
        case GL_CCW : return "GL_CCW";

        case GL_POINT_SIZE : return "GL_POINT_SIZE";
            // GL_SMOOTH_POINT_SIZE_RANGE <=>
        case GL_POINT_SIZE_RANGE : return "GL_POINT_SIZE_RANGE/GL_SMOOTH_POINT_SIZE_RANGE";
            // GL_SMOOTH_POINT_SIZE_GRANULARITY <=>
        case GL_POINT_SIZE_GRANULARITY : return "GL_POINT_SIZE_GRANULARITY/GL_SMOOTH_POINT_SIZE_GRANULARITY";

        case GL_LINE_SMOOTH : return "GL_LINE_SMOOTH";
        case GL_LINE_WIDTH : return "GL_LINE_WIDTH";
            // GL_SMOOTH_LINE_WIDTH_RANGE <=>
        case GL_LINE_WIDTH_RANGE : return "GL_LINE_WIDTH_RANGE/GL_SMOOTH_LINE_WIDTH_RANGE";
            // GL_SMOOTH_LINE_WIDTH_GRANULARITY <=>
        case GL_LINE_WIDTH_GRANULARITY : return "GL_LINE_WIDTH_GRANULARITY/GL_SMOOTH_LINE_WIDTH_GRANULARITY";

        case GL_POLYGON_MODE : return "GL_POLYGON_MODE";
        case GL_POLYGON_SMOOTH : return "GL_POLYGON_SMOOTH";

        case GL_CULL_FACE : return "GL_CULL_FACE";
        case GL_CULL_FACE_MODE : return "GL_CULL_FACE_MODE";
        case GL_FRONT_FACE : return "GL_FRONT_FACE";

        case GL_DEPTH_RANGE : return "GL_DEPTH_RANGE";
        case GL_DEPTH_TEST : return "GL_DEPTH_TEST";
        case GL_DEPTH_WRITEMASK : return "GL_DEPTH_WRITEMASK";
        case GL_DEPTH_CLEAR_VALUE : return "GL_DEPTH_CLEAR_VALUE";
        case GL_DEPTH_FUNC : return "GL_DEPTH_FUNC";

        case GL_STENCIL_TEST : return "GL_STENCIL_TEST";
        case GL_STENCIL_CLEAR_VALUE : return "GL_STENCIL_CLEAR_VALUE";
        case GL_STENCIL_FUNC : return "GL_STENCIL_FUNC";
        case GL_STENCIL_VALUE_MASK : return "GL_STENCIL_VALUE_MASK";
        case GL_STENCIL_FAIL : return "GL_STENCIL_FAIL";
        case GL_STENCIL_PASS_DEPTH_FAIL : return "GL_STENCIL_PASS_DEPTH_FAIL";
        case GL_STENCIL_PASS_DEPTH_PASS : return "GL_STENCIL_PASS_DEPTH_PASS";
        case GL_STENCIL_REF : return "GL_STENCIL_REF";
        case GL_STENCIL_WRITEMASK : return "GL_STENCIL_WRITEMASK";

        case GL_VIEWPORT : return "GL_VIEWPORT";

        case GL_DITHER : return "GL_DITHER";

        case GL_BLEND_DST : return "GL_BLEND_DST";
        case GL_BLEND_SRC : return "GL_BLEND_SRC";
        case GL_BLEND : return "GL_BLEND";

        case GL_LOGIC_OP_MODE : return "GL_LOGIC_OP_MODE";

        case GL_DRAW_BUFFER : return "GL_DRAW_BUFFER";
        case GL_READ_BUFFER : return "GL_READ_BUFFER";

        case GL_SCISSOR_BOX : return "GL_SCISSOR_BOX";
        case GL_SCISSOR_TEST : return "GL_SCISSOR_TEST";

        case GL_COLOR_CLEAR_VALUE : return "GL_COLOR_CLEAR_VALUE";
        case GL_COLOR_WRITEMASK : return "GL_COLOR_WRITEMASK";

        case GL_DOUBLEBUFFER : return "GL_DOUBLEBUFFER";
        case GL_STEREO : return "GL_STEREO";

        case GL_LINE_SMOOTH_HINT : return "GL_LINE_SMOOTH_HINT";
        case GL_POLYGON_SMOOTH_HINT : return "GL_POLYGON_SMOOTH_HINT";

        case GL_UNPACK_SWAP_BYTES : return "GL_UNPACK_SWAP_BYTES";
        case GL_UNPACK_LSB_FIRST : return "GL_UNPACK_LSB_FIRST";
        case GL_UNPACK_ROW_LENGTH : return "GL_UNPACK_ROW_LENGTH";
        case GL_UNPACK_SKIP_ROWS : return "GL_UNPACK_SKIP_ROWS";
        case GL_UNPACK_SKIP_PIXELS : return "GL_UNPACK_SKIP_PIXELS";
        case GL_UNPACK_ALIGNMENT : return "GL_UNPACK_ALIGNMENT";

        case GL_PACK_SWAP_BYTES : return "GL_PACK_SWAP_BYTES";
        case GL_PACK_LSB_FIRST : return "GL_PACK_LSB_FIRST";
        case GL_PACK_ROW_LENGTH : return "GL_PACK_ROW_LENGTH";
        case GL_PACK_SKIP_ROWS : return "GL_PACK_SKIP_ROWS";
        case GL_PACK_SKIP_PIXELS : return "GL_PACK_SKIP_PIXELS";
        case GL_PACK_ALIGNMENT : return "GL_PACK_ALIGNMENT";

        case GL_MAX_TEXTURE_SIZE : return "GL_MAX_TEXTURE_SIZE";
        case GL_MAX_VIEWPORT_DIMS : return "GL_MAX_VIEWPORT_DIMS";

        case GL_SUBPIXEL_BITS : return "GL_SUBPIXEL_BITS";

        case GL_TEXTURE_1D : return "GL_TEXTURE_1D";
        case GL_TEXTURE_2D : return "GL_TEXTURE_2D";
            // GL_TRANSFORM_BIT <=>
        case GL_TEXTURE_WIDTH : return "GL_TEXTURE_WIDTH/GL_TRANSFORM_BIT";
        case GL_TEXTURE_HEIGHT : return "GL_TEXTURE_HEIGHT";
        case GL_TEXTURE_BORDER_COLOR : return "GL_TEXTURE_BORDER_COLOR";

        case GL_DONT_CARE : return "GL_DONT_CARE";
        case GL_FASTEST : return "GL_FASTEST";
        case GL_NICEST : return "GL_NICEST";

        case GL_BYTE : return "GL_BYTE";
        case GL_UNSIGNED_BYTE : return "GL_UNSIGNED_BYTE";
        case GL_SHORT : return "GL_SHORT";
        case GL_UNSIGNED_SHORT : return "GL_UNSIGNED_SHORT";
        case GL_INT : return "GL_INT";
        case GL_UNSIGNED_INT : return "GL_UNSIGNED_INT";
        case GL_FLOAT : return "GL_FLOAT";

        case GL_STACK_OVERFLOW : return "GL_STACK_OVERFLOW";
        case GL_STACK_UNDERFLOW : return "GL_STACK_UNDERFLOW";

        case GL_CLEAR : return "GL_CLEAR";

        case GL_AND : return "GL_AND";
        case GL_AND_REVERSE : return "GL_AND_REVERSE";
        case GL_COPY : return "GL_COPY";
        case GL_AND_INVERTED : return "GL_AND_INVERTED";
        case GL_NOOP : return "GL_NOOP";
        case GL_XOR : return "GL_XOR";
        case GL_OR : return "GL_OR";
        case GL_NOR : return "GL_NOR";
        case GL_EQUIV : return "GL_EQUIV";
        case GL_INVERT : return "GL_INVERT";
        case GL_OR_REVERSE : return "GL_OR_REVERSE";
        case GL_COPY_INVERTED : return "GL_COPY_INVERTED";
        case GL_OR_INVERTED : return "GL_OR_INVERTED";
        case GL_NAND : return "GL_NAND";

        case GL_SET : return "GL_SET";
        case GL_TEXTURE : return "GL_TEXTURE";
        case GL_COLOR : return "GL_COLOR";
        case GL_DEPTH : return "GL_DEPTH";
        case GL_STENCIL : return "GL_STENCIL";
        case GL_STENCIL_INDEX : return "GL_STENCIL_INDEX";
        case GL_DEPTH_COMPONENT : return "GL_DEPTH_COMPONENT";

        case GL_RED : return "GL_RED";
        case GL_GREEN : return "GL_GREEN";
        case GL_BLUE : return "GL_BLUE";
        case GL_ALPHA : return "GL_ALPHA";
        case GL_RGB : return "GL_RGB";
        case GL_RGBA : return "GL_RGBA";

        case GL_POINT : return "GL_POINT";
        case GL_LINE : return "GL_LINE";
        case GL_FILL : return "GL_FILL";
        case GL_KEEP : return "GL_KEEP";
        case GL_REPLACE : return "GL_REPLACE";

        case GL_INCR : return "GL_INCR";
        case GL_DECR : return "GL_DECR";

        case GL_VENDOR : return "GL_VENDOR";
        case GL_RENDERER : return "GL_RENDERER";
        case GL_VERSION : return "GL_VERSION";
        case GL_EXTENSIONS : return "GL_EXTENSIONS";

        case GL_NEAREST : return "GL_NEAREST";
        case GL_LINEAR : return "GL_LINEAR";

        case GL_NEAREST_MIPMAP_NEAREST : return "GL_NEAREST_MIPMAP_NEAREST";
        case GL_LINEAR_MIPMAP_NEAREST : return "GL_LINEAR_MIPMAP_NEAREST";
        case GL_NEAREST_MIPMAP_LINEAR : return "GL_NEAREST_MIPMAP_LINEAR";
        case GL_LINEAR_MIPMAP_LINEAR : return "GL_LINEAR_MIPMAP_LINEAR";

        case GL_TEXTURE_MAG_FILTER : return "GL_TEXTURE_MAG_FILTER";
        case GL_TEXTURE_MIN_FILTER : return "GL_TEXTURE_MIN_FILTER";
        case GL_TEXTURE_WRAP_S : return "GL_TEXTURE_WRAP_S";
        case GL_TEXTURE_WRAP_T : return "GL_TEXTURE_WRAP_T";

        case GL_REPEAT : return "GL_REPEAT";

            // GL_QUAD_STRIP/GL_MAP_INVALIDATE_BUFFER_BIT <=>
        case GL_POLYGON_BIT : return "GL_POLYGON_BIT/GL_QUAD_STRIP/GL_MAP_INVALIDATE_BUFFER_BIT";
            // GL_MAP_FLUSH_EXPLICIT_BIT <=>
        case GL_POLYGON_STIPPLE_BIT : return "GL_POLYGON_STIPPLE_BIT/GL_MAP_FLUSH_EXPLICIT_BIT";
            // GL_MAP_UNSYNCHRONIZED_BIT <=>
        case GL_PIXEL_MODE_BIT : return "GL_PIXEL_MODE_BIT/GL_MAP_UNSYNCHRONIZED_BIT";
        case GL_LIGHTING_BIT : return "GL_LIGHTING_BIT";
        case GL_FOG_BIT : return "GL_FOG_BIT";
            // GL_EXP <=>
        case GL_VIEWPORT_BIT : return "GL_VIEWPORT_BIT/GL_EXP";
            // GL_S <=>
        case GL_ENABLE_BIT : return "GL_ENABLE_BIT/GL_S";
        case GL_HINT_BIT : return "GL_HINT_BIT";
        case GL_EVAL_BIT : return "GL_EVAL_BIT";
        case GL_LIST_BIT : return "GL_LIST_BIT";
        case GL_TEXTURE_BIT : return "GL_TEXTURE_BIT";
        case GL_SCISSOR_BIT : return "GL_SCISSOR_BIT";
            // GL_CLIENT_ALL_ATTRIB_BITS/GL_INVALID_INDEX <=>
        case GL_ALL_ATTRIB_BITS : return "GL_ALL_ATTRIB_BITS/GL_CLIENT_ALL_ATTRIB_BITS/GL_INVALID_INDEX";

        case GL_POLYGON : return "GL_POLYGON";

        case GL_LOAD : return "GL_LOAD";
        case GL_RETURN : return "GL_RETURN";
        case GL_MULT : return "GL_MULT";
        case GL_ADD : return "GL_ADD";

        case GL_AUX0 : return "GL_AUX0";
        case GL_AUX1 : return "GL_AUX1";
        case GL_AUX2 : return "GL_AUX2";
        case GL_AUX3 : return "GL_AUX3";

        case GL_2D : return "GL_2D";
        case GL_3D : return "GL_3D";
        case GL_3D_COLOR : return "GL_3D_COLOR";
        case GL_3D_COLOR_TEXTURE : return "GL_3D_COLOR_TEXTURE";
        case GL_4D_COLOR_TEXTURE : return "GL_4D_COLOR_TEXTURE";

        case GL_PASS_THROUGH_TOKEN : return "GL_PASS_THROUGH_TOKEN";
        case GL_POINT_TOKEN : return "GL_POINT_TOKEN";
        case GL_LINE_TOKEN : return "GL_LINE_TOKEN";
        case GL_POLYGON_TOKEN : return "GL_POLYGON_TOKEN";
        case GL_BITMAP_TOKEN : return "GL_BITMAP_TOKEN";
        case GL_DRAW_PIXEL_TOKEN : return "GL_DRAW_PIXEL_TOKEN";
        case GL_COPY_PIXEL_TOKEN : return "GL_COPY_PIXEL_TOKEN";
        case GL_LINE_RESET_TOKEN : return "GL_LINE_RESET_TOKEN";

        case GL_EXP2 : return "GL_EXP2";
        case GL_COEFF : return "GL_COEFF";
        case GL_ORDER : return "GL_ORDER";
        case GL_DOMAIN : return "GL_DOMAIN";

        case GL_PIXEL_MAP_I_TO_I : return "GL_PIXEL_MAP_I_TO_I";
        case GL_PIXEL_MAP_S_TO_S : return "GL_PIXEL_MAP_S_TO_S";
        case GL_PIXEL_MAP_I_TO_R : return "GL_PIXEL_MAP_I_TO_R";
        case GL_PIXEL_MAP_I_TO_G : return "GL_PIXEL_MAP_I_TO_G";
        case GL_PIXEL_MAP_I_TO_B : return "GL_PIXEL_MAP_I_TO_B";
        case GL_PIXEL_MAP_I_TO_A : return "GL_PIXEL_MAP_I_TO_A";
        case GL_PIXEL_MAP_R_TO_R : return "GL_PIXEL_MAP_R_TO_R";
        case GL_PIXEL_MAP_G_TO_G : return "GL_PIXEL_MAP_G_TO_G";
        case GL_PIXEL_MAP_B_TO_B : return "GL_PIXEL_MAP_B_TO_B";
        case GL_PIXEL_MAP_A_TO_A : return "GL_PIXEL_MAP_A_TO_A";

        case GL_CURRENT_COLOR : return "GL_CURRENT_COLOR";
        case GL_CURRENT_INDEX : return "GL_CURRENT_INDEX";
        case GL_CURRENT_NORMAL : return "GL_CURRENT_NORMAL";
        case GL_CURRENT_TEXTURE_COORDS : return "GL_CURRENT_TEXTURE_COORDS";
        case GL_CURRENT_RASTER_COLOR : return "GL_CURRENT_RASTER_COLOR";
        case GL_CURRENT_RASTER_INDEX : return "GL_CURRENT_RASTER_INDEX";
        case GL_CURRENT_RASTER_TEXTURE_COORDS : return "GL_CURRENT_RASTER_TEXTURE_COORDS";
        case GL_CURRENT_RASTER_POSITION : return "GL_CURRENT_RASTER_POSITION";
        case GL_CURRENT_RASTER_POSITION_VALID : return "GL_CURRENT_RASTER_POSITION_VALID";
        case GL_CURRENT_RASTER_DISTANCE : return "GL_CURRENT_RASTER_DISTANCE";

        case GL_POINT_SMOOTH : return "GL_POINT_SMOOTH";
        case GL_LINE_STIPPLE : return "GL_LINE_STIPPLE";
        case GL_LINE_STIPPLE_PATTERN : return "GL_LINE_STIPPLE_PATTERN";
        case GL_LINE_STIPPLE_REPEAT : return "GL_LINE_STIPPLE_REPEAT";
        case GL_LIST_MODE : return "GL_LIST_MODE";
        case GL_MAX_LIST_NESTING : return "GL_MAX_LIST_NESTING";
        case GL_LIST_BASE : return "GL_LIST_BASE";
        case GL_LIST_INDEX : return "GL_LIST_INDEX";
        case GL_POLYGON_STIPPLE : return "GL_POLYGON_STIPPLE";
        case GL_EDGE_FLAG : return "GL_EDGE_FLAG";

        case GL_LIGHTING : return "GL_LIGHTING";
        case GL_LIGHT_MODEL_LOCAL_VIEWER : return "GL_LIGHT_MODEL_LOCAL_VIEWER";
        case GL_LIGHT_MODEL_TWO_SIDE : return "GL_LIGHT_MODEL_TWO_SIDE";
        case GL_LIGHT_MODEL_AMBIENT : return "GL_LIGHT_MODEL_AMBIENT";

        case GL_SHADE_MODEL : return "GL_SHADE_MODEL";

        case GL_COLOR_MATERIAL_FACE : return "GL_COLOR_MATERIAL_FACE";
        case GL_COLOR_MATERIAL_PARAMETER : return "GL_COLOR_MATERIAL_PARAMETER";
        case GL_COLOR_MATERIAL : return "GL_COLOR_MATERIAL";

        case GL_FOG : return "GL_FOG";
        case GL_FOG_INDEX : return "GL_FOG_INDEX";
        case GL_FOG_DENSITY : return "GL_FOG_DENSITY";
        case GL_FOG_START : return "GL_FOG_START";
        case GL_FOG_END : return "GL_FOG_END";
        case GL_FOG_MODE : return "GL_FOG_MODE";
        case GL_FOG_COLOR : return "GL_FOG_COLOR";

        case GL_ACCUM_CLEAR_VALUE : return "GL_ACCUM_CLEAR_VALUE";
        case GL_MATRIX_MODE : return "GL_MATRIX_MODE";
        case GL_NORMALIZE : return "GL_NORMALIZE";

        case GL_MODELVIEW_STACK_DEPTH : return "GL_MODELVIEW_STACK_DEPTH";
        case GL_PROJECTION_STACK_DEPTH : return "GL_PROJECTION_STACK_DEPTH";
        case GL_TEXTURE_STACK_DEPTH : return "GL_TEXTURE_STACK_DEPTH";

        case GL_MODELVIEW_MATRIX : return "GL_MODELVIEW_MATRIX";
        case GL_PROJECTION_MATRIX : return "GL_PROJECTION_MATRIX";
        case GL_TEXTURE_MATRIX : return "GL_TEXTURE_MATRIX";

        case GL_ATTRIB_STACK_DEPTH : return "GL_ATTRIB_STACK_DEPTH";

        case GL_ALPHA_TEST : return "GL_ALPHA_TEST";
        case GL_ALPHA_TEST_FUNC : return "GL_ALPHA_TEST_FUNC";
        case GL_ALPHA_TEST_REF : return "GL_ALPHA_TEST_REF";

            // GL_INDEX_LOGIC_OP <=>
        case GL_LOGIC_OP : return "GL_LOGIC_OP/GL_INDEX_LOGIC_OP";
        case GL_AUX_BUFFERS : return "GL_AUX_BUFFERS";

        case GL_INDEX_CLEAR_VALUE : return "GL_INDEX_CLEAR_VALUE";
        case GL_INDEX_WRITEMASK : return "GL_INDEX_WRITEMASK";
        case GL_INDEX_MODE : return "GL_INDEX_MODE";

        case GL_RGBA_MODE : return "GL_RGBA_MODE";
        case GL_RENDER_MODE : return "GL_RENDER_MODE";

        case GL_PERSPECTIVE_CORRECTION_HINT : return "GL_PERSPECTIVE_CORRECTION_HINT";
        case GL_POINT_SMOOTH_HINT : return "GL_POINT_SMOOTH_HINT";
        case GL_FOG_HINT : return "GL_FOG_HINT";

        case GL_TEXTURE_GEN_S : return "GL_TEXTURE_GEN_S";
        case GL_TEXTURE_GEN_T : return "GL_TEXTURE_GEN_T";
        case GL_TEXTURE_GEN_R : return "GL_TEXTURE_GEN_R";
        case GL_TEXTURE_GEN_Q : return "GL_TEXTURE_GEN_Q";

        case GL_PIXEL_MAP_I_TO_I_SIZE : return "GL_PIXEL_MAP_I_TO_I_SIZE";
        case GL_PIXEL_MAP_S_TO_S_SIZE : return "GL_PIXEL_MAP_S_TO_S_SIZE";
        case GL_PIXEL_MAP_I_TO_R_SIZE : return "GL_PIXEL_MAP_I_TO_R_SIZE";
        case GL_PIXEL_MAP_I_TO_G_SIZE : return "GL_PIXEL_MAP_I_TO_G_SIZE";
        case GL_PIXEL_MAP_I_TO_B_SIZE : return "GL_PIXEL_MAP_I_TO_B_SIZE";
        case GL_PIXEL_MAP_I_TO_A_SIZE : return "GL_PIXEL_MAP_I_TO_A_SIZE";
        case GL_PIXEL_MAP_R_TO_R_SIZE : return "GL_PIXEL_MAP_R_TO_R_SIZE";
        case GL_PIXEL_MAP_G_TO_G_SIZE : return "GL_PIXEL_MAP_G_TO_G_SIZE";
        case GL_PIXEL_MAP_B_TO_B_SIZE : return "GL_PIXEL_MAP_B_TO_B_SIZE";
        case GL_PIXEL_MAP_A_TO_A_SIZE : return "GL_PIXEL_MAP_A_TO_A_SIZE";

        case GL_MAP_COLOR : return "GL_MAP_COLOR";
        case GL_MAP_STENCIL : return "GL_MAP_STENCIL";

        case GL_INDEX_SHIFT : return "GL_INDEX_SHIFT";
        case GL_INDEX_OFFSET : return "GL_INDEX_OFFSET";

        case GL_RED_SCALE : return "GL_RED_SCALE";
        case GL_RED_BIAS : return "GL_RED_BIAS";

        case GL_ZOOM_X : return "GL_ZOOM_X";
        case GL_ZOOM_Y : return "GL_ZOOM_Y";

        case GL_GREEN_SCALE : return "GL_GREEN_SCALE";
        case GL_GREEN_BIAS : return "GL_GREEN_BIAS";

        case GL_BLUE_SCALE : return "GL_BLUE_SCALE";
        case GL_BLUE_BIAS : return "GL_BLUE_BIAS";

        case GL_ALPHA_SCALE : return "GL_ALPHA_SCALE";
        case GL_ALPHA_BIAS : return "GL_ALPHA_BIAS";

        case GL_DEPTH_SCALE : return "GL_DEPTH_SCALE";
        case GL_DEPTH_BIAS : return "GL_DEPTH_BIAS";

        case GL_MAX_EVAL_ORDER : return "GL_MAX_EVAL_ORDER";
        case GL_MAX_LIGHTS : return "GL_MAX_LIGHTS";
            // GL_MAX_CLIP_DISTANCES <=>
        case GL_MAX_CLIP_PLANES : return "GL_MAX_CLIP_PLANES/GL_MAX_CLIP_DISTANCES";
        case GL_MAX_PIXEL_MAP_TABLE : return "GL_MAX_PIXEL_MAP_TABLE";

        case GL_MAX_ATTRIB_STACK_DEPTH : return "GL_MAX_ATTRIB_STACK_DEPTH";
        case GL_MAX_MODELVIEW_STACK_DEPTH : return "GL_MAX_MODELVIEW_STACK_DEPTH";
        case GL_MAX_NAME_STACK_DEPTH : return "GL_MAX_NAME_STACK_DEPTH";
        case GL_MAX_PROJECTION_STACK_DEPTH : return "GL_MAX_PROJECTION_STACK_DEPTH";
        case GL_MAX_TEXTURE_STACK_DEPTH : return "GL_MAX_TEXTURE_STACK_DEPTH";

        case GL_INDEX_BITS : return "GL_INDEX_BITS";
        case GL_RED_BITS : return "GL_RED_BITS";
        case GL_GREEN_BITS : return "GL_GREEN_BITS";
        case GL_BLUE_BITS : return "GL_BLUE_BITS";
        case GL_ALPHA_BITS : return "GL_ALPHA_BITS";
        case GL_DEPTH_BITS : return "GL_DEPTH_BITS";
        case GL_STENCIL_BITS : return "GL_STENCIL_BITS";
        case GL_ACCUM_RED_BITS : return "GL_ACCUM_RED_BITS";
        case GL_ACCUM_GREEN_BITS : return "GL_ACCUM_GREEN_BITS";
        case GL_ACCUM_BLUE_BITS : return "GL_ACCUM_BLUE_BITS";
        case GL_ACCUM_ALPHA_BITS : return "GL_ACCUM_ALPHA_BITS";

        case GL_NAME_STACK_DEPTH : return "GL_NAME_STACK_DEPTH";
        case GL_AUTO_NORMAL : return "GL_AUTO_NORMAL";

        case GL_MAP1_COLOR_4 : return "GL_MAP1_COLOR_4";
        case GL_MAP1_INDEX : return "GL_MAP1_INDEX";
        case GL_MAP1_NORMAL : return "GL_MAP1_NORMAL";
        case GL_MAP1_TEXTURE_COORD_1 : return "GL_MAP1_TEXTURE_COORD_1";
        case GL_MAP1_TEXTURE_COORD_2 : return "GL_MAP1_TEXTURE_COORD_2";
        case GL_MAP1_TEXTURE_COORD_3 : return "GL_MAP1_TEXTURE_COORD_3";
        case GL_MAP1_TEXTURE_COORD_4 : return "GL_MAP1_TEXTURE_COORD_4";
        case GL_MAP1_VERTEX_3 : return "GL_MAP1_VERTEX_3";
        case GL_MAP1_VERTEX_4 : return "GL_MAP1_VERTEX_4";
        case GL_MAP2_COLOR_4 : return "GL_MAP2_COLOR_4";
        case GL_MAP2_INDEX : return "GL_MAP2_INDEX";
        case GL_MAP2_NORMAL : return "GL_MAP2_NORMAL";
        case GL_MAP2_TEXTURE_COORD_1 : return "GL_MAP2_TEXTURE_COORD_1";
        case GL_MAP2_TEXTURE_COORD_2 : return "GL_MAP2_TEXTURE_COORD_2";
        case GL_MAP2_TEXTURE_COORD_3 : return "GL_MAP2_TEXTURE_COORD_3";
        case GL_MAP2_TEXTURE_COORD_4 : return "GL_MAP2_TEXTURE_COORD_4";
        case GL_MAP2_VERTEX_3 : return "GL_MAP2_VERTEX_3";
        case GL_MAP2_VERTEX_4 : return "GL_MAP2_VERTEX_4";

        case GL_MAP1_GRID_DOMAIN : return "GL_MAP1_GRID_DOMAIN";
        case GL_MAP1_GRID_SEGMENTS : return "GL_MAP1_GRID_SEGMENTS";
        case GL_MAP2_GRID_DOMAIN : return "GL_MAP2_GRID_DOMAIN";
        case GL_MAP2_GRID_SEGMENTS : return "GL_MAP2_GRID_SEGMENTS";

            // GL_TEXTURE_INTERNAL_FORMAT <=>
        case GL_TEXTURE_COMPONENTS : return "GL_TEXTURE_COMPONENTS/GL_TEXTURE_INTERNAL_FORMAT";
        case GL_TEXTURE_BORDER : return "GL_TEXTURE_BORDER";

        case GL_AMBIENT : return "GL_AMBIENT";
        case GL_DIFFUSE : return "GL_DIFFUSE";
        case GL_SPECULAR : return "GL_SPECULAR";
        case GL_POSITION : return "GL_POSITION";

        case GL_SPOT_DIRECTION : return "GL_SPOT_DIRECTION";
        case GL_SPOT_EXPONENT : return "GL_SPOT_EXPONENT";
        case GL_SPOT_CUTOFF : return "GL_SPOT_CUTOFF";

        case GL_CONSTANT_ATTENUATION : return "GL_CONSTANT_ATTENUATION";
        case GL_LINEAR_ATTENUATION : return "GL_LINEAR_ATTENUATION";
        case GL_QUADRATIC_ATTENUATION : return "GL_QUADRATIC_ATTENUATION";

        case GL_COMPILE : return "GL_COMPILE";
        case GL_COMPILE_AND_EXECUTE : return "GL_COMPILE_AND_EXECUTE";

        case GL_2_BYTES : return "GL_2_BYTES";
        case GL_3_BYTES : return "GL_3_BYTES";
        case GL_4_BYTES : return "GL_4_BYTES";

        case GL_EMISSION : return "GL_EMISSION";
        case GL_SHININESS : return "GL_SHININESS";
        case GL_AMBIENT_AND_DIFFUSE : return "GL_AMBIENT_AND_DIFFUSE";
        case GL_COLOR_INDEXES : return "GL_COLOR_INDEXES";

        case GL_MODELVIEW : return "GL_MODELVIEW";
        case GL_PROJECTION : return "GL_PROJECTION";

        case GL_COLOR_INDEX : return "GL_COLOR_INDEX";
        case GL_LUMINANCE : return "GL_LUMINANCE";
        case GL_LUMINANCE_ALPHA : return "GL_LUMINANCE_ALPHA";
        case GL_BITMAP : return "GL_BITMAP";

        case GL_RENDER : return "GL_RENDER";
        case GL_FEEDBACK : return "GL_FEEDBACK";
        case GL_SELECT : return "GL_SELECT";

        case GL_FLAT : return "GL_FLAT";
        case GL_SMOOTH : return "GL_SMOOTH";

        case GL_T : return "GL_T";
        case GL_R : return "GL_R";
        case GL_Q : return "GL_Q";

        case GL_MODULATE : return "GL_MODULATE";
        case GL_DECAL : return "GL_DECAL";

        case GL_TEXTURE_ENV_MODE : return "GL_TEXTURE_ENV_MODE";
        case GL_TEXTURE_ENV_COLOR : return "GL_TEXTURE_ENV_COLOR";
        case GL_TEXTURE_ENV : return "GL_TEXTURE_ENV";

        case GL_EYE_LINEAR : return "GL_EYE_LINEAR";
        case GL_OBJECT_LINEAR : return "GL_OBJECT_LINEAR";

        case GL_SPHERE_MAP : return "GL_SPHERE_MAP";
        case GL_TEXTURE_GEN_MODE : return "GL_TEXTURE_GEN_MODE";

        case GL_OBJECT_PLANE : return "GL_OBJECT_PLANE";
        case GL_EYE_PLANE : return "GL_EYE_PLANE";

        case GL_CLAMP : return "GL_CLAMP";

            // GL_CLIP_DISTANCE0 <=>
        case GL_CLIP_PLANE0 : return "GL_CLIP_PLANE0/GL_CLIP_DISTANCE0";
            // GL_CLIP_DISTANCE1 <=>
        case GL_CLIP_PLANE1 : return "GL_CLIP_PLANE1/GL_CLIP_DISTANCE1";
            // GL_CLIP_DISTANCE2 <=>
        case GL_CLIP_PLANE2 : return "GL_CLIP_PLANE2/GL_CLIP_DISTANCE2";
            // GL_CLIP_DISTANCE3 <=>
        case GL_CLIP_PLANE3 : return "GL_CLIP_PLANE3/GL_CLIP_DISTANCE3";
            // GL_CLIP_DISTANCE4 <=>
        case GL_CLIP_PLANE4 : return "GL_CLIP_PLANE4/GL_CLIP_DISTANCE4";
            // GL_CLIP_DISTANCE5 <=>
        case GL_CLIP_PLANE5 : return "GL_CLIP_PLANE5/GL_CLIP_DISTANCE5";

        case GL_LIGHT1 : return "GL_LIGHT1";
        case GL_LIGHT2 : return "GL_LIGHT2";
        case GL_LIGHT3 : return "GL_LIGHT3";
        case GL_LIGHT4 : return "GL_LIGHT4";
        case GL_LIGHT5 : return "GL_LIGHT5";
        case GL_LIGHT6 : return "GL_LIGHT6";
        case GL_LIGHT7 : return "GL_LIGHT7";

        case GL_COLOR_LOGIC_OP : return "GL_COLOR_LOGIC_OP";

        case GL_POLYGON_OFFSET_UNITS : return "GL_POLYGON_OFFSET_UNITS";
        case GL_POLYGON_OFFSET_POINT : return "GL_POLYGON_OFFSET_POINT";
        case GL_POLYGON_OFFSET_LINE : return "GL_POLYGON_OFFSET_LINE";
        case GL_POLYGON_OFFSET_FILL : return "GL_POLYGON_OFFSET_FILL";
        case GL_POLYGON_OFFSET_FACTOR : return "GL_POLYGON_OFFSET_FACTOR";

        case GL_TEXTURE_BINDING_1D : return "GL_TEXTURE_BINDING_1D";
        case GL_TEXTURE_BINDING_2D : return "GL_TEXTURE_BINDING_2D";
            // case GL_TEXTURE_INTERNAL_FORMAT <=> case GL_TEXTURE_COMPONENTS
        case GL_TEXTURE_RED_SIZE : return "GL_TEXTURE_RED_SIZE";
        case GL_TEXTURE_GREEN_SIZE : return "GL_TEXTURE_GREEN_SIZE";

        case GL_TEXTURE_BLUE_SIZE : return "GL_TEXTURE_BLUE_SIZE";
        case GL_TEXTURE_ALPHA_SIZE : return "GL_TEXTURE_ALPHA_SIZE";

        case GL_DOUBLE : return "GL_DOUBLE";

        case GL_PROXY_TEXTURE_1D : return "GL_PROXY_TEXTURE_1D";
        case GL_PROXY_TEXTURE_2D : return "GL_PROXY_TEXTURE_2D";

        case GL_R3_G3_B2 : return "GL_R3_G3_B2";
        case GL_RGB4 : return "GL_RGB4";
        case GL_RGB5 : return "GL_RGB5";
        case GL_RGB8 : return "GL_RGB8";
        case GL_RGB10 : return "GL_RGB10";
        case GL_RGB12 : return "GL_RGB12";
        case GL_RGB16 : return "GL_RGB16";

        case GL_RGBA2 : return "GL_RGBA2";
        case GL_RGBA4 : return "GL_RGBA4";
        case GL_RGB5_A1 : return "GL_RGB5_A1";
        case GL_RGBA8 : return "GL_RGBA8";
        case GL_RGB10_A2 : return "GL_RGB10_A2";
        case GL_RGBA12 : return "GL_RGBA12";
        case GL_RGBA16 : return "GL_RGBA16";

            // case GL_CLIENT_PIXEL_STORE_BIT <=> case GL_LINE_LOOP
            // case GL_CLIENT_VERTEX_ARRAY_BIT <=> case GL_LINE_LOOP
            // case GL_CLIENT_ALL_ATTRIB_BITS <=> case GL_ALL_ATTRIB_BITS

        case GL_VERTEX_ARRAY_POINTER : return "GL_VERTEX_ARRAY_POINTER";
        case GL_NORMAL_ARRAY_POINTER : return "GL_NORMAL_ARRAY_POINTER";
        case GL_COLOR_ARRAY_POINTER : return "GL_COLOR_ARRAY_POINTER";
        case GL_INDEX_ARRAY_POINTER : return "GL_INDEX_ARRAY_POINTER";
        case GL_TEXTURE_COORD_ARRAY_POINTER : return "GL_TEXTURE_COORD_ARRAY_POINTER";
        case GL_EDGE_FLAG_ARRAY_POINTER : return "GL_EDGE_FLAG_ARRAY_POINTER";
        case GL_FEEDBACK_BUFFER_POINTER : return "GL_FEEDBACK_BUFFER_POINTER";
        case GL_SELECTION_BUFFER_POINTER : return "GL_SELECTION_BUFFER_POINTER";

        case GL_CLIENT_ATTRIB_STACK_DEPTH : return "GL_CLIENT_ATTRIB_STACK_DEPTH";
            // case GL_INDEX_LOGIC_OP <=> case GL_LOGIC_OP
        case GL_MAX_CLIENT_ATTRIB_STACK_DEPTH : return "GL_MAX_CLIENT_ATTRIB_STACK_DEPTH";

        case GL_FEEDBACK_BUFFER_SIZE : return "GL_FEEDBACK_BUFFER_SIZE";
        case GL_FEEDBACK_BUFFER_TYPE : return "GL_FEEDBACK_BUFFER_TYPE";
        case GL_SELECTION_BUFFER_SIZE : return "GL_SELECTION_BUFFER_SIZE";

        case GL_VERTEX_ARRAY : return "GL_VERTEX_ARRAY";
        case GL_NORMAL_ARRAY : return "GL_NORMAL_ARRAY";
        case GL_COLOR_ARRAY : return "GL_COLOR_ARRAY";
        case GL_INDEX_ARRAY : return "GL_INDEX_ARRAY";
        case GL_TEXTURE_COORD_ARRAY : return "GL_TEXTURE_COORD_ARRAY";
        case GL_EDGE_FLAG_ARRAY : return "GL_EDGE_FLAG_ARRAY";

        case GL_VERTEX_ARRAY_SIZE : return "GL_VERTEX_ARRAY_SIZE";

        case GL_VERTEX_ARRAY_TYPE : return "GL_VERTEX_ARRAY_TYPE";
        case GL_VERTEX_ARRAY_STRIDE : return "GL_VERTEX_ARRAY_STRIDE";
        case GL_NORMAL_ARRAY_TYPE : return "GL_NORMAL_ARRAY_TYPE";
        case GL_NORMAL_ARRAY_STRIDE : return "GL_NORMAL_ARRAY_STRIDE";

        case GL_COLOR_ARRAY_SIZE : return "GL_COLOR_ARRAY_SIZE";
        case GL_COLOR_ARRAY_TYPE : return "GL_COLOR_ARRAY_TYPE";
        case GL_COLOR_ARRAY_STRIDE : return "GL_COLOR_ARRAY_STRIDE";
        case GL_INDEX_ARRAY_TYPE : return "GL_INDEX_ARRAY_TYPE";
        case GL_INDEX_ARRAY_STRIDE : return "GL_INDEX_ARRAY_STRIDE";

        case GL_TEXTURE_COORD_ARRAY_SIZE : return "GL_TEXTURE_COORD_ARRAY_SIZE";
        case GL_TEXTURE_COORD_ARRAY_TYPE : return "GL_TEXTURE_COORD_ARRAY_TYPE";

        case GL_TEXTURE_COORD_ARRAY_STRIDE : return "GL_TEXTURE_COORD_ARRAY_STRIDE";
        case GL_EDGE_FLAG_ARRAY_STRIDE : return "GL_EDGE_FLAG_ARRAY_STRIDE";

        case GL_TEXTURE_LUMINANCE_SIZE : return "GL_TEXTURE_LUMINANCE_SIZE";
        case GL_TEXTURE_INTENSITY_SIZE : return "GL_TEXTURE_INTENSITY_SIZE";
        case GL_TEXTURE_PRIORITY : return "GL_TEXTURE_PRIORITY";
        case GL_TEXTURE_RESIDENT : return "GL_TEXTURE_RESIDENT";

        case GL_ALPHA4 : return "GL_ALPHA4";
        case GL_ALPHA8 : return "GL_ALPHA8";
        case GL_ALPHA12 : return "GL_ALPHA12";
        case GL_ALPHA16 : return "GL_ALPHA16";

        case GL_LUMINANCE4 : return "GL_LUMINANCE4";
        case GL_LUMINANCE8 : return "GL_LUMINANCE8";
        case GL_LUMINANCE12 : return "GL_LUMINANCE12";

        case GL_LUMINANCE16 : return "GL_LUMINANCE16";

        case GL_LUMINANCE4_ALPHA4 : return "GL_LUMINANCE4_ALPHA4";
        case GL_LUMINANCE6_ALPHA2 : return "GL_LUMINANCE6_ALPHA2";
        case GL_LUMINANCE8_ALPHA8 : return "GL_LUMINANCE8_ALPHA8";
        case GL_LUMINANCE12_ALPHA4 : return "GL_LUMINANCE12_ALPHA4";
        case GL_LUMINANCE12_ALPHA12 : return "GL_LUMINANCE12_ALPHA12";
        case GL_LUMINANCE16_ALPHA16 : return "GL_LUMINANCE16_ALPHA16";

        case GL_INTENSITY : return "GL_INTENSITY";
        case GL_INTENSITY4 : return "GL_INTENSITY4";
        case GL_INTENSITY8 : return "GL_INTENSITY8";
        case GL_INTENSITY12 : return "GL_INTENSITY12";
        case GL_INTENSITY16 : return "GL_INTENSITY16";

        case GL_V2F : return "GL_V2F";
        case GL_V3F : return "GL_V3F";
        case GL_C4UB_V2F : return "GL_C4UB_V2F";
        case GL_C4UB_V3F : return "GL_C4UB_V3F";
        case GL_C3F_V3F : return "GL_C3F_V3F";
        case GL_N3F_V3F : return "GL_N3F_V3F";
        case GL_C4F_N3F_V3F : return "GL_C4F_N3F_V3F";
        case GL_T2F_V3F : return "GL_T2F_V3F";
        case GL_T4F_V4F : return "GL_T4F_V4F";
        case GL_T2F_C4UB_V3F : return "GL_T2F_C4UB_V3F";
        case GL_T2F_C3F_V3F : return "GL_T2F_C3F_V3F";
        case GL_T2F_N3F_V3F : return "GL_T2F_N3F_V3F";
        case GL_T2F_C4F_N3F_V3F : return "GL_T2F_C4F_N3F_V3F";

        case GL_T4F_C4F_N3F_V4F : return "GL_T4F_C4F_N3F_V4F";

        case GL_UNSIGNED_BYTE_3_3_2 : return "GL_UNSIGNED_BYTE_3_3_2";
        case GL_UNSIGNED_SHORT_4_4_4_4 : return "GL_UNSIGNED_SHORT_4_4_4_4";
        case GL_UNSIGNED_SHORT_5_5_5_1 : return "GL_UNSIGNED_SHORT_5_5_5_1";
        case GL_UNSIGNED_INT_8_8_8_8 : return "GL_UNSIGNED_INT_8_8_8_8";
        case GL_UNSIGNED_INT_10_10_10_2 : return "GL_UNSIGNED_INT_10_10_10_2";

        case GL_TEXTURE_BINDING_3D : return "GL_TEXTURE_BINDING_3D";
        case GL_PACK_SKIP_IMAGES : return "GL_PACK_SKIP_IMAGES";
        case GL_PACK_IMAGE_HEIGHT : return "GL_PACK_IMAGE_HEIGHT";
        case GL_UNPACK_SKIP_IMAGES : return "GL_UNPACK_SKIP_IMAGES";
        case GL_UNPACK_IMAGE_HEIGHT : return "GL_UNPACK_IMAGE_HEIGHT";

        case GL_TEXTURE_3D : return "GL_TEXTURE_3D";

        case GL_PROXY_TEXTURE_3D : return "GL_PROXY_TEXTURE_3D";
        case GL_TEXTURE_DEPTH : return "GL_TEXTURE_DEPTH";
        case GL_TEXTURE_WRAP_R : return "GL_TEXTURE_WRAP_R";
        case GL_MAX_3D_TEXTURE_SIZE : return "GL_MAX_3D_TEXTURE_SIZE";

        case GL_UNSIGNED_BYTE_2_3_3_REV : return "GL_UNSIGNED_BYTE_2_3_3_REV";
        case GL_UNSIGNED_SHORT_5_6_5 : return "GL_UNSIGNED_SHORT_5_6_5";
        case GL_UNSIGNED_SHORT_5_6_5_REV : return "GL_UNSIGNED_SHORT_5_6_5_REV";
        case GL_UNSIGNED_SHORT_4_4_4_4_REV : return "GL_UNSIGNED_SHORT_4_4_4_4_REV";
        case GL_UNSIGNED_SHORT_1_5_5_5_REV : return "GL_UNSIGNED_SHORT_1_5_5_5_REV";
        case GL_UNSIGNED_INT_8_8_8_8_REV : return "GL_UNSIGNED_INT_8_8_8_8_REV";
        case GL_UNSIGNED_INT_2_10_10_10_REV : return "GL_UNSIGNED_INT_2_10_10_10_REV";

        case GL_BGR : return "GL_BGR";
        case GL_BGRA : return "GL_BGRA";
        case GL_MAX_ELEMENTS_VERTICES : return "GL_MAX_ELEMENTS_VERTICES";
        case GL_MAX_ELEMENTS_INDICES : return "GL_MAX_ELEMENTS_INDICES";
        case GL_CLAMP_TO_EDGE : return "GL_CLAMP_TO_EDGE";
        case GL_TEXTURE_MIN_LOD : return "GL_TEXTURE_MIN_LOD";
        case GL_TEXTURE_MAX_LOD : return "GL_TEXTURE_MAX_LOD";
        case GL_TEXTURE_BASE_LEVEL : return "GL_TEXTURE_BASE_LEVEL";
        case GL_TEXTURE_MAX_LEVEL : return "GL_TEXTURE_MAX_LEVEL";
            // case GL_SMOOTH_POINT_SIZE_RANGE <=> case GL_POINT_SIZE_RANGE

            // case GL_SMOOTH_POINT_SIZE_GRANULARITY <=> case GL_POINT_SIZE_GRANULARITY
            // case GL_SMOOTH_LINE_WIDTH_RANGE <=> case GL_LINE_WIDTH_RANGE
            // case GL_SMOOTH_LINE_WIDTH_GRANULARITY <=> case GL_LINE_WIDTH_GRANULARITY
        case GL_ALIASED_LINE_WIDTH_RANGE : return "GL_ALIASED_LINE_WIDTH_RANGE";
        case GL_RESCALE_NORMAL : return "GL_RESCALE_NORMAL";
        case GL_LIGHT_MODEL_COLOR_CONTROL : return "GL_LIGHT_MODEL_COLOR_CONTROL";
        case GL_SINGLE_COLOR : return "GL_SINGLE_COLOR";
        case GL_SEPARATE_SPECULAR_COLOR : return "GL_SEPARATE_SPECULAR_COLOR";
        case GL_ALIASED_POINT_SIZE_RANGE : return "GL_ALIASED_POINT_SIZE_RANGE";

        case GL_TEXTURE0 : return "GL_TEXTURE0";
        case GL_TEXTURE1 : return "GL_TEXTURE1";
        case GL_TEXTURE2 : return "GL_TEXTURE2";
        case GL_TEXTURE3 : return "GL_TEXTURE3";
        case GL_TEXTURE4 : return "GL_TEXTURE4";
        case GL_TEXTURE5 : return "GL_TEXTURE5";
        case GL_TEXTURE6 : return "GL_TEXTURE6";
        case GL_TEXTURE7 : return "GL_TEXTURE7";
        case GL_TEXTURE8 : return "GL_TEXTURE8";
        case GL_TEXTURE9 : return "GL_TEXTURE9";
        case GL_TEXTURE10 : return "GL_TEXTURE10";
        case GL_TEXTURE11 : return "GL_TEXTURE11";
        case GL_TEXTURE12 : return "GL_TEXTURE12";
        case GL_TEXTURE13 : return "GL_TEXTURE13";
        case GL_TEXTURE14 : return "GL_TEXTURE14";
        case GL_TEXTURE15 : return "GL_TEXTURE15";
        case GL_TEXTURE16 : return "GL_TEXTURE16";
        case GL_TEXTURE17 : return "GL_TEXTURE17";
        case GL_TEXTURE18 : return "GL_TEXTURE18";
        case GL_TEXTURE19 : return "GL_TEXTURE19";
        case GL_TEXTURE20 : return "GL_TEXTURE20";
        case GL_TEXTURE21 : return "GL_TEXTURE21";
        case GL_TEXTURE22 : return "GL_TEXTURE22";
        case GL_TEXTURE23 : return "GL_TEXTURE23";
        case GL_TEXTURE24 : return "GL_TEXTURE24";
        case GL_TEXTURE25 : return "GL_TEXTURE25";
        case GL_TEXTURE26 : return "GL_TEXTURE26";
        case GL_TEXTURE27 : return "GL_TEXTURE27";
        case GL_TEXTURE28 : return "GL_TEXTURE28";
        case GL_TEXTURE29 : return "GL_TEXTURE29";
        case GL_TEXTURE30 : return "GL_TEXTURE30";
        case GL_TEXTURE31 : return "GL_TEXTURE31";

        case GL_ACTIVE_TEXTURE : return "GL_ACTIVE_TEXTURE";

        case GL_MULTISAMPLE : return "GL_MULTISAMPLE";
        case GL_SAMPLE_ALPHA_TO_COVERAGE : return "GL_SAMPLE_ALPHA_TO_COVERAGE";
        case GL_SAMPLE_ALPHA_TO_ONE : return "GL_SAMPLE_ALPHA_TO_ONE";
        case GL_SAMPLE_COVERAGE : return "GL_SAMPLE_COVERAGE";
        case GL_SAMPLE_BUFFERS : return "GL_SAMPLE_BUFFERS";
        case GL_SAMPLES : return "GL_SAMPLES";
        case GL_SAMPLE_COVERAGE_VALUE : return "GL_SAMPLE_COVERAGE_VALUE";
        case GL_SAMPLE_COVERAGE_INVERT : return "GL_SAMPLE_COVERAGE_INVERT";

        case GL_TEXTURE_CUBE_MAP : return "GL_TEXTURE_CUBE_MAP";
        case GL_TEXTURE_BINDING_CUBE_MAP : return "GL_TEXTURE_BINDING_CUBE_MAP";
        case GL_TEXTURE_CUBE_MAP_POSITIVE_X : return "GL_TEXTURE_CUBE_MAP_POSITIVE_X";
        case GL_TEXTURE_CUBE_MAP_NEGATIVE_X : return "GL_TEXTURE_CUBE_MAP_NEGATIVE_X";
        case GL_TEXTURE_CUBE_MAP_POSITIVE_Y : return "GL_TEXTURE_CUBE_MAP_POSITIVE_Y";
        case GL_TEXTURE_CUBE_MAP_NEGATIVE_Y : return "GL_TEXTURE_CUBE_MAP_NEGATIVE_Y";
        case GL_TEXTURE_CUBE_MAP_POSITIVE_Z : return "GL_TEXTURE_CUBE_MAP_POSITIVE_Z";
        case GL_TEXTURE_CUBE_MAP_NEGATIVE_Z : return "GL_TEXTURE_CUBE_MAP_NEGATIVE_Z";

        case GL_PROXY_TEXTURE_CUBE_MAP : return "GL_PROXY_TEXTURE_CUBE_MAP";
        case GL_MAX_CUBE_MAP_TEXTURE_SIZE : return "GL_MAX_CUBE_MAP_TEXTURE_SIZE";

        case GL_COMPRESSED_RGB : return "GL_COMPRESSED_RGB";
        case GL_COMPRESSED_RGBA : return "GL_COMPRESSED_RGBA";

        case GL_TEXTURE_COMPRESSION_HINT : return "GL_TEXTURE_COMPRESSION_HINT";
        case GL_TEXTURE_COMPRESSED_IMAGE_SIZE : return "GL_TEXTURE_COMPRESSED_IMAGE_SIZE";
        case GL_TEXTURE_COMPRESSED : return "GL_TEXTURE_COMPRESSED";
        case GL_NUM_COMPRESSED_TEXTURE_FORMATS : return "GL_NUM_COMPRESSED_TEXTURE_FORMATS";
        case GL_COMPRESSED_TEXTURE_FORMATS : return "GL_COMPRESSED_TEXTURE_FORMATS";

        case GL_CLAMP_TO_BORDER : return "GL_CLAMP_TO_BORDER";

        case GL_CLIENT_ACTIVE_TEXTURE : return "GL_CLIENT_ACTIVE_TEXTURE";
        case GL_MAX_TEXTURE_UNITS : return "GL_MAX_TEXTURE_UNITS";

        case GL_TRANSPOSE_MODELVIEW_MATRIX : return "GL_TRANSPOSE_MODELVIEW_MATRIX";
        case GL_TRANSPOSE_PROJECTION_MATRIX : return "GL_TRANSPOSE_PROJECTION_MATRIX";
        case GL_TRANSPOSE_TEXTURE_MATRIX : return "GL_TRANSPOSE_TEXTURE_MATRIX";
        case GL_TRANSPOSE_COLOR_MATRIX : return "GL_TRANSPOSE_COLOR_MATRIX";

        case GL_MULTISAMPLE_BIT : return "GL_MULTISAMPLE_BIT";

        case GL_NORMAL_MAP : return "GL_NORMAL_MAP";
        case GL_REFLECTION_MAP : return "GL_REFLECTION_MAP";

        case GL_COMPRESSED_ALPHA : return "GL_COMPRESSED_ALPHA";
        case GL_COMPRESSED_LUMINANCE : return "GL_COMPRESSED_LUMINANCE";
        case GL_COMPRESSED_LUMINANCE_ALPHA : return "GL_COMPRESSED_LUMINANCE_ALPHA";
        case GL_COMPRESSED_INTENSITY : return "GL_COMPRESSED_INTENSITY";

        case GL_COMBINE : return "GL_COMBINE";
        case GL_COMBINE_RGB : return "GL_COMBINE_RGB";
        case GL_COMBINE_ALPHA : return "GL_COMBINE_ALPHA";

            // GL_SRC0_RGB
        case GL_SOURCE0_RGB : return "GL_SOURCE0_RGB/GL_SRC0_RGB";
            // GL_SRC1_RGB
        case GL_SOURCE1_RGB : return "GL_SOURCE1_RGB/GL_SRC1_RGB";
            // GL_SRC2_RGB
        case GL_SOURCE2_RGB : return "GL_SOURCE2_RGB/GL_SRC2_RGB";

            // GL_SRC0_ALPHA
        case GL_SOURCE0_ALPHA : return "GL_SOURCE0_ALPHA/GL_SRC0_ALPHA";
            // GL_SRC1_ALPHA
        case GL_SOURCE1_ALPHA : return "GL_SOURCE1_ALPHA/GL_SRC1_ALPHA";
            // GL_SRC2_ALPHA
        case GL_SOURCE2_ALPHA : return "GL_SOURCE2_ALPHA/GL_SRC2_ALPHA";

        case GL_OPERAND0_RGB : return "GL_OPERAND0_RGB";
        case GL_OPERAND1_RGB : return "GL_OPERAND1_RGB";
        case GL_OPERAND2_RGB : return "GL_OPERAND2_RGB";

        case GL_OPERAND0_ALPHA : return "GL_OPERAND0_ALPHA";
        case GL_OPERAND1_ALPHA : return "GL_OPERAND1_ALPHA";
        case GL_OPERAND2_ALPHA : return "GL_OPERAND2_ALPHA";

        case GL_RGB_SCALE : return "GL_RGB_SCALE";

        case GL_ADD_SIGNED : return "GL_ADD_SIGNED";
        case GL_INTERPOLATE : return "GL_INTERPOLATE";
        case GL_SUBTRACT : return "GL_SUBTRACT";
        case GL_CONSTANT : return "GL_CONSTANT";
        case GL_PRIMARY_COLOR : return "GL_PRIMARY_COLOR";
        case GL_PREVIOUS : return "GL_PREVIOUS";

        case GL_DOT3_RGB : return "GL_DOT3_RGB";
        case GL_DOT3_RGBA : return "GL_DOT3_RGBA";

        case GL_BLEND_DST_RGB : return "GL_BLEND_DST_RGB";
        case GL_BLEND_SRC_RGB : return "GL_BLEND_SRC_RGB";
        case GL_BLEND_DST_ALPHA : return "GL_BLEND_DST_ALPHA";

        case GL_BLEND_SRC_ALPHA : return "GL_BLEND_SRC_ALPHA";

        case GL_POINT_FADE_THRESHOLD_SIZE : return "GL_POINT_FADE_THRESHOLD_SIZE";

        case GL_DEPTH_COMPONENT16 : return "GL_DEPTH_COMPONENT16";
        case GL_DEPTH_COMPONENT24 : return "GL_DEPTH_COMPONENT24";
        case GL_DEPTH_COMPONENT32 : return "GL_DEPTH_COMPONENT32";

        case GL_MIRRORED_REPEAT : return "GL_MIRRORED_REPEAT";
        case GL_MAX_TEXTURE_LOD_BIAS : return "GL_MAX_TEXTURE_LOD_BIAS";
        case GL_TEXTURE_LOD_BIAS : return "GL_TEXTURE_LOD_BIAS";

        case GL_INCR_WRAP : return "GL_INCR_WRAP";
        case GL_DECR_WRAP : return "GL_DECR_WRAP";

        case GL_TEXTURE_DEPTH_SIZE : return "GL_TEXTURE_DEPTH_SIZE";
        case GL_TEXTURE_COMPARE_MODE : return "GL_TEXTURE_COMPARE_MODE";
        case GL_TEXTURE_COMPARE_FUNC : return "GL_TEXTURE_COMPARE_FUNC";

        case GL_POINT_SIZE_MIN : return "GL_POINT_SIZE_MIN";
        case GL_POINT_SIZE_MAX : return "GL_POINT_SIZE_MAX";

        case GL_POINT_DISTANCE_ATTENUATION : return "GL_POINT_DISTANCE_ATTENUATION";
        case GL_GENERATE_MIPMAP : return "GL_GENERATE_MIPMAP";
        case GL_GENERATE_MIPMAP_HINT : return "GL_GENERATE_MIPMAP_HINT";

            // GL_FOG_COORD_SRC
        case GL_FOG_COORDINATE_SOURCE : return "GL_FOG_COORDINATE_SOURCE/GL_FOG_COORD_SRC";
            // GL_FOG_COORD
        case GL_FOG_COORDINATE : return "GL_FOG_COORDINATE/GL_FOG_COORD";

        case GL_FRAGMENT_DEPTH : return "GL_FRAGMENT_DEPTH";

            // GL_CURRENT_FOG_COORD
        case GL_CURRENT_FOG_COORDINATE : return "GL_CURRENT_FOG_COORDINATE/GL_CURRENT_FOG_COORD";
            // GL_FOG_COORD_ARRAY_TYPE
        case GL_FOG_COORDINATE_ARRAY_TYPE : return "GL_FOG_COORDINATE_ARRAY_TYPE/GL_FOG_COORD_ARRAY_TYPE";
            // GL_FOG_COORD_ARRAY_STRIDE
        case GL_FOG_COORDINATE_ARRAY_STRIDE : return "GL_FOG_COORDINATE_ARRAY_STRIDE/GL_FOG_COORD_ARRAY_STRIDE";
            // GL_FOG_COORD_ARRAY_POINTER
        case GL_FOG_COORDINATE_ARRAY_POINTER : return "GL_FOG_COORDINATE_ARRAY_POINTER/GL_FOG_COORD_ARRAY_POINTER";
            // GL_FOG_COORD_ARRAY
        case GL_FOG_COORDINATE_ARRAY : return "GL_FOG_COORDINATE_ARRAY/GL_FOG_COORD_ARRAY";

        case GL_COLOR_SUM : return "GL_COLOR_SUM";

        case GL_CURRENT_SECONDARY_COLOR : return "GL_CURRENT_SECONDARY_COLOR";
        case GL_SECONDARY_COLOR_ARRAY_SIZE : return "GL_SECONDARY_COLOR_ARRAY_SIZE";
        case GL_SECONDARY_COLOR_ARRAY_TYPE : return "GL_SECONDARY_COLOR_ARRAY_TYPE";
        case GL_SECONDARY_COLOR_ARRAY_STRIDE : return "GL_SECONDARY_COLOR_ARRAY_STRIDE";
        case GL_SECONDARY_COLOR_ARRAY_POINTER : return "GL_SECONDARY_COLOR_ARRAY_POINTER";
        case GL_SECONDARY_COLOR_ARRAY : return "GL_SECONDARY_COLOR_ARRAY";

        case GL_TEXTURE_FILTER_CONTROL : return "GL_TEXTURE_FILTER_CONTROL";
        case GL_DEPTH_TEXTURE_MODE : return "GL_DEPTH_TEXTURE_MODE";
            // GL_COMPARE_REF_TO_TEXTURE
        case GL_COMPARE_R_TO_TEXTURE : return "GL_COMPARE_R_TO_TEXTURE/GL_COMPARE_REF_TO_TEXTURE";

        case GL_BLEND_COLOR : return "GL_BLEND_COLOR";
            // GL_BLEND_EQUATION_RGB
        case GL_BLEND_EQUATION : return "GL_BLEND_EQUATION/GL_BLEND_EQUATION_RGB";

        case GL_CONSTANT_COLOR : return "GL_CONSTANT_COLOR";
        case GL_ONE_MINUS_CONSTANT_COLOR : return "GL_ONE_MINUS_CONSTANT_COLOR";
        case GL_CONSTANT_ALPHA : return "GL_CONSTANT_ALPHA";
        case GL_ONE_MINUS_CONSTANT_ALPHA : return "GL_ONE_MINUS_CONSTANT_ALPHA";

        case GL_FUNC_ADD : return "GL_FUNC_ADD";
        case GL_FUNC_REVERSE_SUBTRACT : return "GL_FUNC_REVERSE_SUBTRACT";
        case GL_FUNC_SUBTRACT : return "GL_FUNC_SUBTRACT";

        case GL_MIN : return "GL_MIN";
        case GL_MAX : return "GL_MAX";

        case GL_BUFFER_SIZE : return "GL_BUFFER_SIZE";
        case GL_BUFFER_USAGE : return "GL_BUFFER_USAGE";

        case GL_QUERY_COUNTER_BITS : return "GL_QUERY_COUNTER_BITS";
        case GL_CURRENT_QUERY : return "GL_CURRENT_QUERY";
        case GL_QUERY_RESULT : return "GL_QUERY_RESULT";
        case GL_QUERY_RESULT_AVAILABLE : return "GL_QUERY_RESULT_AVAILABLE";

        case GL_ELEMENT_ARRAY_BUFFER_BINDING : return "GL_ELEMENT_ARRAY_BUFFER_BINDING";
        case GL_VERTEX_ATTRIB_ARRAY_BUFFER_BINDING : return "GL_VERTEX_ATTRIB_ARRAY_BUFFER_BINDING";

        case GL_READ_ONLY : return "GL_READ_ONLY";
        case GL_WRITE_ONLY : return "GL_WRITE_ONLY";
        case GL_READ_WRITE : return "GL_READ_WRITE";

        case GL_BUFFER_ACCESS : return "GL_BUFFER_ACCESS";
        case GL_BUFFER_MAPPED : return "GL_BUFFER_MAPPED";
        case GL_BUFFER_MAP_POINTER : return "GL_BUFFER_MAP_POINTER";

            // case GL_SRC1_ALPHA <=> case GL_SOURCE1_ALPHA

        case GL_VERTEX_ARRAY_BUFFER_BINDING : return "GL_VERTEX_ARRAY_BUFFER_BINDING";
        case GL_NORMAL_ARRAY_BUFFER_BINDING : return "GL_NORMAL_ARRAY_BUFFER_BINDING";
        case GL_COLOR_ARRAY_BUFFER_BINDING : return "GL_COLOR_ARRAY_BUFFER_BINDING";
        case GL_INDEX_ARRAY_BUFFER_BINDING : return "GL_INDEX_ARRAY_BUFFER_BINDING";
        case GL_TEXTURE_COORD_ARRAY_BUFFER_BINDING : return "GL_TEXTURE_COORD_ARRAY_BUFFER_BINDING";
        case GL_EDGE_FLAG_ARRAY_BUFFER_BINDING : return "GL_EDGE_FLAG_ARRAY_BUFFER_BINDING";
        case GL_SECONDARY_COLOR_ARRAY_BUFFER_BINDING : return "GL_SECONDARY_COLOR_ARRAY_BUFFER_BINDING";
            // GL_FOG_COORD_ARRAY_BUFFER_BINDING
        case GL_FOG_COORDINATE_ARRAY_BUFFER_BINDING : return "GL_FOG_COORDINATE_ARRAY_BUFFER_BINDING/"
                                                             "GL_FOG_COORD_ARRAY_BUFFER_BINDING";
        case GL_WEIGHT_ARRAY_BUFFER_BINDING : return "GL_WEIGHT_ARRAY_BUFFER_BINDING";

            // case GL_FOG_COORD_SRC <=> case GL_FOG_COORDINATE_SOURCE
            // case GL_FOG_COORD <=> case GL_FOG_COORDINATE
            // case GL_CURRENT_FOG_COORD <=> case GL_CURRENT_FOG_COORDINATE
            // case GL_FOG_COORD_ARRAY_TYPE <=> case GL_FOG_COORDINATE_ARRAY_TYPE
            // case GL_FOG_COORD_ARRAY_STRIDE <=> case GL_FOG_COORDINATE_ARRAY_STRIDE
            // case GL_FOG_COORD_ARRAY_POINTER <=> case GL_FOG_COORDINATE_ARRAY_POINTER
            // case GL_FOG_COORD_ARRAY <=> case GL_FOG_COORDINATE_ARRAY
            // case GL_FOG_COORD_ARRAY_BUFFER_BINDING <=> case GL_FOG_COORDINATE_ARRAY_BUFFER_BINDING

            // case GL_SRC0_RGB <=> case GL_SOURCE0_RGB
            // case GL_SRC1_RGB <=> case GL_SOURCE1_RGB
            // case GL_SRC2_RGB <=> case GL_SOURCE2_RGB

            // case GL_SRC0_ALPHA <=> case GL_SOURCE0_ALPHA
            // case GL_SRC2_ALPHA <=> case GL_SOURCE2_ALPHA

            // case GL_BLEND_EQUATION_RGB <=> case GL_BLEND_EQUATION

        case GL_VERTEX_ATTRIB_ARRAY_ENABLED : return "GL_VERTEX_ATTRIB_ARRAY_ENABLED";
        case GL_VERTEX_ATTRIB_ARRAY_SIZE : return "GL_VERTEX_ATTRIB_ARRAY_SIZE";
        case GL_VERTEX_ATTRIB_ARRAY_STRIDE : return "GL_VERTEX_ATTRIB_ARRAY_STRIDE";
        case GL_VERTEX_ATTRIB_ARRAY_TYPE : return "GL_VERTEX_ATTRIB_ARRAY_TYPE";
        case GL_CURRENT_VERTEX_ATTRIB : return "GL_CURRENT_VERTEX_ATTRIB";

            // GL_PROGRAM_POINT_SIZE
        case GL_VERTEX_PROGRAM_POINT_SIZE : return "GL_VERTEX_PROGRAM_POINT_SIZE/GL_PROGRAM_POINT_SIZE";
        case GL_VERTEX_ATTRIB_ARRAY_POINTER : return "GL_VERTEX_ATTRIB_ARRAY_POINTER";

        case GL_STENCIL_BACK_FUNC : return "GL_STENCIL_BACK_FUNC";
        case GL_STENCIL_BACK_FAIL : return "GL_STENCIL_BACK_FAIL";
        case GL_STENCIL_BACK_PASS_DEPTH_FAIL : return "GL_STENCIL_BACK_PASS_DEPTH_FAIL";
        case GL_STENCIL_BACK_PASS_DEPTH_PASS : return "GL_STENCIL_BACK_PASS_DEPTH_PASS";

        case GL_MAX_DRAW_BUFFERS : return "GL_MAX_DRAW_BUFFERS";
        case GL_DRAW_BUFFER0 : return "GL_DRAW_BUFFER0";
        case GL_DRAW_BUFFER1 : return "GL_DRAW_BUFFER1";
        case GL_DRAW_BUFFER2 : return "GL_DRAW_BUFFER2";
        case GL_DRAW_BUFFER3 : return "GL_DRAW_BUFFER3";
        case GL_DRAW_BUFFER4 : return "GL_DRAW_BUFFER4";
        case GL_DRAW_BUFFER5 : return "GL_DRAW_BUFFER5";
        case GL_DRAW_BUFFER6 : return "GL_DRAW_BUFFER6";
        case GL_DRAW_BUFFER7 : return "GL_DRAW_BUFFER7";
        case GL_DRAW_BUFFER8 : return "GL_DRAW_BUFFER8";
        case GL_DRAW_BUFFER9 : return "GL_DRAW_BUFFER9";
        case GL_DRAW_BUFFER10 : return "GL_DRAW_BUFFER10";
        case GL_DRAW_BUFFER11 : return "GL_DRAW_BUFFER11";
        case GL_DRAW_BUFFER12 : return "GL_DRAW_BUFFER12";
        case GL_DRAW_BUFFER13 : return "GL_DRAW_BUFFER13";
        case GL_DRAW_BUFFER14 : return "GL_DRAW_BUFFER14";
        case GL_DRAW_BUFFER15 : return "GL_DRAW_BUFFER15";

        case GL_BLEND_EQUATION_ALPHA : return "GL_BLEND_EQUATION_ALPHA";

        case GL_MAX_VERTEX_ATTRIBS : return "GL_MAX_VERTEX_ATTRIBS";
        case GL_VERTEX_ATTRIB_ARRAY_NORMALIZED : return "GL_VERTEX_ATTRIB_ARRAY_NORMALIZED";
        case GL_MAX_TEXTURE_IMAGE_UNITS : return "GL_MAX_TEXTURE_IMAGE_UNITS";

        case GL_MAX_FRAGMENT_UNIFORM_COMPONENTS : return "GL_MAX_FRAGMENT_UNIFORM_COMPONENTS";
        case GL_MAX_VERTEX_UNIFORM_COMPONENTS : return "GL_MAX_VERTEX_UNIFORM_COMPONENTS";
            // GL_MAX_VARYING_COMPONENTS
        case GL_MAX_VARYING_FLOATS : return "GL_MAX_VARYING_FLOATS/GL_MAX_VARYING_COMPONENTS";
        case GL_MAX_VERTEX_TEXTURE_IMAGE_UNITS : return "GL_MAX_VERTEX_TEXTURE_IMAGE_UNITS";
        case GL_MAX_COMBINED_TEXTURE_IMAGE_UNITS : return "GL_MAX_COMBINED_TEXTURE_IMAGE_UNITS";

        case GL_SHADER_TYPE : return "GL_SHADER_TYPE";

        case GL_FLOAT_VEC2 : return "GL_FLOAT_VEC2";
        case GL_FLOAT_VEC3 : return "GL_FLOAT_VEC3";
        case GL_FLOAT_VEC4 : return "GL_FLOAT_VEC4";

        case GL_INT_VEC2 : return "GL_INT_VEC2";
        case GL_INT_VEC3 : return "GL_INT_VEC3";
        case GL_INT_VEC4 : return "GL_INT_VEC4";

        case GL_BOOL : return "GL_BOOL";
        case GL_BOOL_VEC2 : return "GL_BOOL_VEC2";
        case GL_BOOL_VEC3 : return "GL_BOOL_VEC3";
        case GL_BOOL_VEC4 : return "GL_BOOL_VEC4";

        case GL_FLOAT_MAT2 : return "GL_FLOAT_MAT2";
        case GL_FLOAT_MAT3 : return "GL_FLOAT_MAT3";
        case GL_FLOAT_MAT4 : return "GL_FLOAT_MAT4";

        case GL_SAMPLER_1D : return "GL_SAMPLER_1D";
        case GL_SAMPLER_2D : return "GL_SAMPLER_2D";
        case GL_SAMPLER_3D : return "GL_SAMPLER_3D";
        case GL_SAMPLER_CUBE : return "GL_SAMPLER_CUBE";
        case GL_SAMPLER_1D_SHADOW : return "GL_SAMPLER_1D_SHADOW";
        case GL_SAMPLER_2D_SHADOW : return "GL_SAMPLER_2D_SHADOW";

        case GL_DELETE_STATUS : return "GL_DELETE_STATUS";
        case GL_COMPILE_STATUS : return "GL_COMPILE_STATUS";
        case GL_LINK_STATUS : return "GL_LINK_STATUS";
        case GL_VALIDATE_STATUS : return "GL_VALIDATE_STATUS";

        case GL_INFO_LOG_LENGTH : return "GL_INFO_LOG_LENGTH";
        case GL_ATTACHED_SHADERS : return "GL_ATTACHED_SHADERS";

        case GL_ACTIVE_UNIFORMS : return "GL_ACTIVE_UNIFORMS";
        case GL_ACTIVE_UNIFORM_MAX_LENGTH : return "GL_ACTIVE_UNIFORM_MAX_LENGTH";

        case GL_SHADER_SOURCE_LENGTH : return "GL_SHADER_SOURCE_LENGTH";

        case GL_ACTIVE_ATTRIBUTES : return "GL_ACTIVE_ATTRIBUTES";
        case GL_ACTIVE_ATTRIBUTE_MAX_LENGTH : return "GL_ACTIVE_ATTRIBUTE_MAX_LENGTH";

        case GL_FRAGMENT_SHADER_DERIVATIVE_HINT : return "GL_FRAGMENT_SHADER_DERIVATIVE_HINT";

        case GL_SHADING_LANGUAGE_VERSION : return "GL_SHADING_LANGUAGE_VERSION";
        case GL_CURRENT_PROGRAM : return "GL_CURRENT_PROGRAM";
        case GL_POINT_SPRITE_COORD_ORIGIN : return "GL_POINT_SPRITE_COORD_ORIGIN";

        case GL_LOWER_LEFT : return "GL_LOWER_LEFT";
        case GL_UPPER_LEFT : return "GL_UPPER_LEFT";

        case GL_STENCIL_BACK_REF : return "GL_STENCIL_BACK_REF";
        case GL_STENCIL_BACK_VALUE_MASK : return "GL_STENCIL_BACK_VALUE_MASK";
        case GL_STENCIL_BACK_WRITEMASK : return "GL_STENCIL_BACK_WRITEMASK";

        case GL_VERTEX_PROGRAM_TWO_SIDE : return "GL_VERTEX_PROGRAM_TWO_SIDE";
        case GL_POINT_SPRITE : return "GL_POINT_SPRITE";
        case GL_COORD_REPLACE : return "GL_COORD_REPLACE";
        case GL_MAX_TEXTURE_COORDS : return "GL_MAX_TEXTURE_COORDS";

        case GL_PIXEL_PACK_BUFFER : return "GL_PIXEL_PACK_BUFFER";
        case GL_PIXEL_UNPACK_BUFFER : return "GL_PIXEL_UNPACK_BUFFER";
        case GL_PIXEL_PACK_BUFFER_BINDING : return "GL_PIXEL_PACK_BUFFER_BINDING";
        case GL_PIXEL_UNPACK_BUFFER_BINDING : return "GL_PIXEL_UNPACK_BUFFER_BINDING";

        case GL_FLOAT_MAT2x3 : return "GL_FLOAT_MAT2x3";
        case GL_FLOAT_MAT2x4 : return "GL_FLOAT_MAT2x4";
        case GL_FLOAT_MAT3x2 : return "GL_FLOAT_MAT3x2";
        case GL_FLOAT_MAT3x4 : return "GL_FLOAT_MAT3x4";
        case GL_FLOAT_MAT4x2 : return "GL_FLOAT_MAT4x2";
        case GL_FLOAT_MAT4x3 : return "GL_FLOAT_MAT4x3";

        case GL_SRGB : return "GL_SRGB";
        case GL_SRGB8 : return "GL_SRGB8";
        case GL_SRGB_ALPHA : return "GL_SRGB_ALPHA";
        case GL_SRGB8_ALPHA8 : return "GL_SRGB8_ALPHA8";
        case GL_COMPRESSED_SRGB : return "GL_COMPRESSED_SRGB";
        case GL_COMPRESSED_SRGB_ALPHA : return "GL_COMPRESSED_SRGB_ALPHA";

        case GL_CURRENT_RASTER_SECONDARY_COLOR : return "GL_CURRENT_RASTER_SECONDARY_COLOR";

        case GL_SLUMINANCE_ALPHA : return "GL_SLUMINANCE_ALPHA";
        case GL_SLUMINANCE8_ALPHA8 : return "GL_SLUMINANCE8_ALPHA8";
        case GL_SLUMINANCE : return "GL_SLUMINANCE";
        case GL_SLUMINANCE8 : return "GL_SLUMINANCE8";
        case GL_COMPRESSED_SLUMINANCE : return "GL_COMPRESSED_SLUMINANCE";
        case GL_COMPRESSED_SLUMINANCE_ALPHA : return "GL_COMPRESSED_SLUMINANCE_ALPHA";

            // case GL_COMPARE_REF_TO_TEXTURE <=> case GL_COMPARE_R_TO_TEXTURE

            // case GL_CLIP_DISTANCE0 <=> case GL_CLIP_PLANE0
            // case GL_CLIP_DISTANCE1 <=> case GL_CLIP_PLANE1
            // case GL_CLIP_DISTANCE2 <=> case GL_CLIP_PLANE2
            // case GL_CLIP_DISTANCE3 <=> case GL_CLIP_PLANE3
            // case GL_CLIP_DISTANCE4 <=> case GL_CLIP_PLANE4
            // case GL_CLIP_DISTANCE5 <=> case GL_CLIP_PLANE5
        case GL_CLIP_DISTANCE6 : return "GL_CLIP_DISTANCE6";
        case GL_CLIP_DISTANCE7 : return "GL_CLIP_DISTANCE7";
            // case GL_MAX_CLIP_DISTANCES <=> case GL_MAX_CLIP_PLANES

        case GL_MAJOR_VERSION : return "GL_MAJOR_VERSION";
        case GL_MINOR_VERSION : return "GL_MINOR_VERSION";
        case GL_NUM_EXTENSIONS : return "GL_NUM_EXTENSIONS";
        case GL_CONTEXT_FLAGS : return "GL_CONTEXT_FLAGS";

        case GL_COMPRESSED_RED : return "GL_COMPRESSED_RED";
        case GL_COMPRESSED_RG : return "GL_COMPRESSED_RG";

            // case GL_CONTEXT_FLAG_FORWARD_COMPATIBLE_BIT <=> case GL_TRUE

        case GL_RGBA32F : return "GL_RGBA32F";
        case GL_RGB32F : return "GL_RGB32F";
        case GL_RGBA16F : return "GL_RGBA16F";
        case GL_RGB16F : return "GL_RGB16F";

        case GL_VERTEX_ATTRIB_ARRAY_INTEGER : return "GL_VERTEX_ATTRIB_ARRAY_INTEGER";

        case GL_MAX_ARRAY_TEXTURE_LAYERS : return "GL_MAX_ARRAY_TEXTURE_LAYERS";
        case GL_MIN_PROGRAM_TEXEL_OFFSET : return "GL_MIN_PROGRAM_TEXEL_OFFSET";
        case GL_MAX_PROGRAM_TEXEL_OFFSET : return "GL_MAX_PROGRAM_TEXEL_OFFSET";

        case GL_CLAMP_READ_COLOR : return "GL_CLAMP_READ_COLOR";

        case GL_FIXED_ONLY : return "GL_FIXED_ONLY";

            // case GL_MAX_VARYING_COMPONENTS <=> case GL_MAX_VARYING_FLOATS

        case GL_TEXTURE_1D_ARRAY : return "GL_TEXTURE_1D_ARRAY";
        case GL_PROXY_TEXTURE_1D_ARRAY : return "GL_PROXY_TEXTURE_1D_ARRAY";
        case GL_TEXTURE_2D_ARRAY : return "GL_TEXTURE_2D_ARRAY";
        case GL_PROXY_TEXTURE_2D_ARRAY : return "GL_PROXY_TEXTURE_2D_ARRAY";
        case GL_TEXTURE_BINDING_1D_ARRAY : return "GL_TEXTURE_BINDING_1D_ARRAY";
        case GL_TEXTURE_BINDING_2D_ARRAY : return "GL_TEXTURE_BINDING_2D_ARRAY";

        case GL_R11F_G11F_B10F : return "GL_R11F_G11F_B10F";
        case GL_UNSIGNED_INT_10F_11F_11F_REV : return "GL_UNSIGNED_INT_10F_11F_11F_REV";

        case GL_RGB9_E5 : return "GL_RGB9_E5";
        case GL_UNSIGNED_INT_5_9_9_9_REV : return "GL_UNSIGNED_INT_5_9_9_9_REV";

        case GL_TEXTURE_SHARED_SIZE : return "GL_TEXTURE_SHARED_SIZE";

        case GL_TRANSFORM_FEEDBACK_VARYING_MAX_LENGTH : return "GL_TRANSFORM_FEEDBACK_VARYING_MAX_LENGTH";
        case GL_TRANSFORM_FEEDBACK_BUFFER_MODE : return "GL_TRANSFORM_FEEDBACK_BUFFER_MODE";
        case GL_MAX_TRANSFORM_FEEDBACK_SEPARATE_COMPONENTS : return "GL_MAX_TRANSFORM_FEEDBACK_SEPARATE_COMPONENTS";
        case GL_TRANSFORM_FEEDBACK_VARYINGS : return "GL_TRANSFORM_FEEDBACK_VARYINGS";
        case GL_TRANSFORM_FEEDBACK_BUFFER_START : return "GL_TRANSFORM_FEEDBACK_BUFFER_START";
        case GL_TRANSFORM_FEEDBACK_BUFFER_SIZE : return "GL_TRANSFORM_FEEDBACK_BUFFER_SIZE";

        case GL_PRIMITIVES_GENERATED : return "GL_PRIMITIVES_GENERATED";

        case GL_TRANSFORM_FEEDBACK_PRIMITIVES_WRITTEN : return "GL_TRANSFORM_FEEDBACK_PRIMITIVES_WRITTEN";

        case GL_RASTERIZER_DISCARD : return "GL_RASTERIZER_DISCARD";

        case GL_MAX_TRANSFORM_FEEDBACK_INTERLEAVED_COMPONENTS : return "GL_MAX_TRANSFORM_FEEDBACK_INTERLEAVED_COMPONENTS";
        case GL_MAX_TRANSFORM_FEEDBACK_SEPARATE_ATTRIBS : return "GL_MAX_TRANSFORM_FEEDBACK_SEPARATE_ATTRIBS";
        case GL_INTERLEAVED_ATTRIBS : return "GL_INTERLEAVED_ATTRIBS";
        case GL_SEPARATE_ATTRIBS : return "GL_SEPARATE_ATTRIBS";

        case GL_TRANSFORM_FEEDBACK_BUFFER : return "GL_TRANSFORM_FEEDBACK_BUFFER";
        case GL_TRANSFORM_FEEDBACK_BUFFER_BINDING : return "GL_TRANSFORM_FEEDBACK_BUFFER_BINDING";

        case GL_RGBA32UI : return "GL_RGBA32UI";
        case GL_RGB32UI : return "GL_RGB32UI";
        case GL_RGBA16UI : return "GL_RGBA16UI";
        case GL_RGB16UI : return "GL_RGB16UI";
        case GL_RGBA8UI : return "GL_RGBA8UI";
        case GL_RGB8UI : return "GL_RGB8UI";
        case GL_RGBA32I : return "GL_RGBA32I";
        case GL_RGB32I : return "GL_RGB32I";
        case GL_RGBA16I : return "GL_RGBA16I";
        case GL_RGB16I : return "GL_RGB16I";
        case GL_RGBA8I : return "GL_RGBA8I";
        case GL_RGB8I : return "GL_RGB8I";

        case GL_RED_INTEGER : return "GL_RED_INTEGER";
        case GL_GREEN_INTEGER : return "GL_GREEN_INTEGER";
        case GL_BLUE_INTEGER : return "GL_BLUE_INTEGER";

        case GL_RGB_INTEGER : return "GL_RGB_INTEGER";
        case GL_RGBA_INTEGER : return "GL_RGBA_INTEGER";
        case GL_BGR_INTEGER : return "GL_BGR_INTEGER";
        case GL_BGRA_INTEGER : return "GL_BGRA_INTEGER";

        case GL_SAMPLER_1D_ARRAY : return "GL_SAMPLER_1D_ARRAY";
        case GL_SAMPLER_2D_ARRAY : return "GL_SAMPLER_2D_ARRAY";
        case GL_SAMPLER_1D_ARRAY_SHADOW : return "GL_SAMPLER_1D_ARRAY_SHADOW";
        case GL_SAMPLER_2D_ARRAY_SHADOW : return "GL_SAMPLER_2D_ARRAY_SHADOW";
        case GL_SAMPLER_CUBE_SHADOW : return "GL_SAMPLER_CUBE_SHADOW";

        case GL_UNSIGNED_INT_VEC2 : return "GL_UNSIGNED_INT_VEC2";
        case GL_UNSIGNED_INT_VEC3 : return "GL_UNSIGNED_INT_VEC3";
        case GL_UNSIGNED_INT_VEC4 : return "GL_UNSIGNED_INT_VEC4";

        case GL_INT_SAMPLER_1D : return "GL_INT_SAMPLER_1D";
        case GL_INT_SAMPLER_2D : return "GL_INT_SAMPLER_2D";
        case GL_INT_SAMPLER_3D : return "GL_INT_SAMPLER_3D";
        case GL_INT_SAMPLER_CUBE : return "GL_INT_SAMPLER_CUBE";
        case GL_INT_SAMPLER_1D_ARRAY : return "GL_INT_SAMPLER_1D_ARRAY";
        case GL_INT_SAMPLER_2D_ARRAY : return "GL_INT_SAMPLER_2D_ARRAY";

        case GL_UNSIGNED_INT_SAMPLER_1D : return "GL_UNSIGNED_INT_SAMPLER_1D";
        case GL_UNSIGNED_INT_SAMPLER_2D : return "GL_UNSIGNED_INT_SAMPLER_2D";
        case GL_UNSIGNED_INT_SAMPLER_3D : return "GL_UNSIGNED_INT_SAMPLER_3D";
        case GL_UNSIGNED_INT_SAMPLER_CUBE : return "GL_UNSIGNED_INT_SAMPLER_CUBE";
        case GL_UNSIGNED_INT_SAMPLER_1D_ARRAY : return "GL_UNSIGNED_INT_SAMPLER_1D_ARRAY";
        case GL_UNSIGNED_INT_SAMPLER_2D_ARRAY : return "GL_UNSIGNED_INT_SAMPLER_2D_ARRAY";

        case GL_QUERY_WAIT : return "GL_QUERY_WAIT";
        case GL_QUERY_NO_WAIT : return "GL_QUERY_NO_WAIT";
        case GL_QUERY_BY_REGION_WAIT : return "GL_QUERY_BY_REGION_WAIT";
        case GL_QUERY_BY_REGION_NO_WAIT : return "GL_QUERY_BY_REGION_NO_WAIT";

        case GL_BUFFER_ACCESS_FLAGS : return "GL_BUFFER_ACCESS_FLAGS";
        case GL_BUFFER_MAP_LENGTH : return "GL_BUFFER_MAP_LENGTH";
        case GL_BUFFER_MAP_OFFSET : return "GL_BUFFER_MAP_OFFSET";

        case GL_DEPTH_COMPONENT32F : return "GL_DEPTH_COMPONENT32F";
        case GL_DEPTH32F_STENCIL8 : return "GL_DEPTH32F_STENCIL8";

        case GL_FLOAT_32_UNSIGNED_INT_24_8_REV : return "GL_FLOAT_32_UNSIGNED_INT_24_8_REV";

        case GL_INVALID_FRAMEBUFFER_OPERATION : return "GL_INVALID_FRAMEBUFFER_OPERATION";
        case GL_FRAMEBUFFER_ATTACHMENT_COLOR_ENCODING : return "GL_FRAMEBUFFER_ATTACHMENT_COLOR_ENCODING";
        case GL_FRAMEBUFFER_ATTACHMENT_COMPONENT_TYPE : return "GL_FRAMEBUFFER_ATTACHMENT_COMPONENT_TYPE";

        case GL_FRAMEBUFFER_ATTACHMENT_RED_SIZE : return "GL_FRAMEBUFFER_ATTACHMENT_RED_SIZE";
        case GL_FRAMEBUFFER_ATTACHMENT_GREEN_SIZE : return "GL_FRAMEBUFFER_ATTACHMENT_GREEN_SIZE";
        case GL_FRAMEBUFFER_ATTACHMENT_BLUE_SIZE : return "GL_FRAMEBUFFER_ATTACHMENT_BLUE_SIZE";
        case GL_FRAMEBUFFER_ATTACHMENT_ALPHA_SIZE : return "GL_FRAMEBUFFER_ATTACHMENT_ALPHA_SIZE";
        case GL_FRAMEBUFFER_ATTACHMENT_DEPTH_SIZE : return "GL_FRAMEBUFFER_ATTACHMENT_DEPTH_SIZE";
        case GL_FRAMEBUFFER_ATTACHMENT_STENCIL_SIZE : return "GL_FRAMEBUFFER_ATTACHMENT_STENCIL_SIZE";

        case GL_FRAMEBUFFER_DEFAULT : return "GL_FRAMEBUFFER_DEFAULT";
        case GL_FRAMEBUFFER_UNDEFINED : return "GL_FRAMEBUFFER_UNDEFINED";

        case GL_DEPTH_STENCIL_ATTACHMENT : return "GL_DEPTH_STENCIL_ATTACHMENT";
        case GL_MAX_RENDERBUFFER_SIZE : return "GL_MAX_RENDERBUFFER_SIZE";

        case GL_DEPTH_STENCIL : return "GL_DEPTH_STENCIL";
        case GL_UNSIGNED_INT_24_8 : return "GL_UNSIGNED_INT_24_8";
        case GL_DEPTH24_STENCIL8 : return "GL_DEPTH24_STENCIL8";

        case GL_TEXTURE_STENCIL_SIZE : return "GL_TEXTURE_STENCIL_SIZE";
        case GL_TEXTURE_RED_TYPE : return "GL_TEXTURE_RED_TYPE";
        case GL_TEXTURE_GREEN_TYPE : return "GL_TEXTURE_GREEN_TYPE";
        case GL_TEXTURE_BLUE_TYPE : return "GL_TEXTURE_BLUE_TYPE";
        case GL_TEXTURE_ALPHA_TYPE : return "GL_TEXTURE_ALPHA_TYPE";
        case GL_TEXTURE_DEPTH_TYPE : return "GL_TEXTURE_DEPTH_TYPE";

        case GL_UNSIGNED_NORMALIZED : return "GL_UNSIGNED_NORMALIZED";

            // GL_DRAW_FRAMEBUFFER_BINDING
        case GL_FRAMEBUFFER_BINDING : return "GL_FRAMEBUFFER_BINDING/GL_DRAW_FRAMEBUFFER_BINDING";
            // case GL_DRAW_FRAMEBUFFER_BINDING <=> case GL_FRAMEBUFFER_BINDING
        case GL_RENDERBUFFER_BINDING : return "GL_RENDERBUFFER_BINDING";

        case GL_READ_FRAMEBUFFER : return "GL_READ_FRAMEBUFFER";
        case GL_DRAW_FRAMEBUFFER : return "GL_DRAW_FRAMEBUFFER";
        case GL_READ_FRAMEBUFFER_BINDING : return "GL_READ_FRAMEBUFFER_BINDING";

        case GL_RENDERBUFFER_SAMPLES : return "GL_RENDERBUFFER_SAMPLES";

        case GL_FRAMEBUFFER_ATTACHMENT_OBJECT_TYPE : return "GL_FRAMEBUFFER_ATTACHMENT_OBJECT_TYPE";
        case GL_FRAMEBUFFER_ATTACHMENT_OBJECT_NAME : return "GL_FRAMEBUFFER_ATTACHMENT_OBJECT_NAME";
        case GL_FRAMEBUFFER_ATTACHMENT_TEXTURE_LEVEL : return "GL_FRAMEBUFFER_ATTACHMENT_TEXTURE_LEVEL";
        case GL_FRAMEBUFFER_ATTACHMENT_TEXTURE_CUBE_MAP_FACE : return "GL_FRAMEBUFFER_ATTACHMENT_TEXTURE_CUBE_MAP_FACE";
        case GL_FRAMEBUFFER_ATTACHMENT_TEXTURE_LAYER : return "GL_FRAMEBUFFER_ATTACHMENT_TEXTURE_LAYER";
        case GL_FRAMEBUFFER_COMPLETE : return "GL_FRAMEBUFFER_COMPLETE";
        case GL_FRAMEBUFFER_INCOMPLETE_ATTACHMENT : return "GL_FRAMEBUFFER_INCOMPLETE_ATTACHMENT";
        case GL_FRAMEBUFFER_INCOMPLETE_MISSING_ATTACHMENT : return "GL_FRAMEBUFFER_INCOMPLETE_MISSING_ATTACHMENT";

        case GL_FRAMEBUFFER_INCOMPLETE_DRAW_BUFFER : return "GL_FRAMEBUFFER_INCOMPLETE_DRAW_BUFFER";
        case GL_FRAMEBUFFER_INCOMPLETE_READ_BUFFER : return "GL_FRAMEBUFFER_INCOMPLETE_READ_BUFFER";
        case GL_FRAMEBUFFER_UNSUPPORTED : return "GL_FRAMEBUFFER_UNSUPPORTED";
        case GL_MAX_COLOR_ATTACHMENTS : return "GL_MAX_COLOR_ATTACHMENTS";

        case GL_COLOR_ATTACHMENT0 : return "GL_COLOR_ATTACHMENT0";
        case GL_COLOR_ATTACHMENT1 : return "GL_COLOR_ATTACHMENT1";
        case GL_COLOR_ATTACHMENT2 : return "GL_COLOR_ATTACHMENT2";
        case GL_COLOR_ATTACHMENT3 : return "GL_COLOR_ATTACHMENT3";
        case GL_COLOR_ATTACHMENT4 : return "GL_COLOR_ATTACHMENT4";
        case GL_COLOR_ATTACHMENT5 : return "GL_COLOR_ATTACHMENT5";
        case GL_COLOR_ATTACHMENT6 : return "GL_COLOR_ATTACHMENT6";
        case GL_COLOR_ATTACHMENT7 : return "GL_COLOR_ATTACHMENT7";
        case GL_COLOR_ATTACHMENT8 : return "GL_COLOR_ATTACHMENT8";
        case GL_COLOR_ATTACHMENT9 : return "GL_COLOR_ATTACHMENT9";
        case GL_COLOR_ATTACHMENT10 : return "GL_COLOR_ATTACHMENT10";
        case GL_COLOR_ATTACHMENT11 : return "GL_COLOR_ATTACHMENT11";
        case GL_COLOR_ATTACHMENT12 : return "GL_COLOR_ATTACHMENT12";
        case GL_COLOR_ATTACHMENT13 : return "GL_COLOR_ATTACHMENT13";
        case GL_COLOR_ATTACHMENT14 : return "GL_COLOR_ATTACHMENT14";
        case GL_COLOR_ATTACHMENT15 : return "GL_COLOR_ATTACHMENT15";
        case GL_COLOR_ATTACHMENT16 : return "GL_COLOR_ATTACHMENT16";
        case GL_COLOR_ATTACHMENT17 : return "GL_COLOR_ATTACHMENT17";
        case GL_COLOR_ATTACHMENT18 : return "GL_COLOR_ATTACHMENT18";
        case GL_COLOR_ATTACHMENT19 : return "GL_COLOR_ATTACHMENT19";
        case GL_COLOR_ATTACHMENT20 : return "GL_COLOR_ATTACHMENT20";
        case GL_COLOR_ATTACHMENT21 : return "GL_COLOR_ATTACHMENT21";
        case GL_COLOR_ATTACHMENT22 : return "GL_COLOR_ATTACHMENT22";
        case GL_COLOR_ATTACHMENT23 : return "GL_COLOR_ATTACHMENT23";
        case GL_COLOR_ATTACHMENT24 : return "GL_COLOR_ATTACHMENT24";
        case GL_COLOR_ATTACHMENT25 : return "GL_COLOR_ATTACHMENT25";
        case GL_COLOR_ATTACHMENT26 : return "GL_COLOR_ATTACHMENT26";
        case GL_COLOR_ATTACHMENT27 : return "GL_COLOR_ATTACHMENT27";
        case GL_COLOR_ATTACHMENT28 : return "GL_COLOR_ATTACHMENT28";
        case GL_COLOR_ATTACHMENT29 : return "GL_COLOR_ATTACHMENT29";
        case GL_COLOR_ATTACHMENT30 : return "GL_COLOR_ATTACHMENT30";
        case GL_COLOR_ATTACHMENT31 : return "GL_COLOR_ATTACHMENT31";

        case GL_DEPTH_ATTACHMENT : return "GL_DEPTH_ATTACHMENT";
        case GL_STENCIL_ATTACHMENT : return "GL_STENCIL_ATTACHMENT";

        case GL_FRAMEBUFFER : return "GL_FRAMEBUFFER";
        case GL_RENDERBUFFER : return "GL_RENDERBUFFER";
        case GL_RENDERBUFFER_WIDTH : return "GL_RENDERBUFFER_WIDTH";
        case GL_RENDERBUFFER_HEIGHT : return "GL_RENDERBUFFER_HEIGHT";
        case GL_RENDERBUFFER_INTERNAL_FORMAT : return "GL_RENDERBUFFER_INTERNAL_FORMAT";

        case GL_STENCIL_INDEX1 : return "GL_STENCIL_INDEX1";
        case GL_STENCIL_INDEX4 : return "GL_STENCIL_INDEX4";
        case GL_STENCIL_INDEX8 : return "GL_STENCIL_INDEX8";
        case GL_STENCIL_INDEX16 : return "GL_STENCIL_INDEX16";

        case GL_RENDERBUFFER_RED_SIZE : return "GL_RENDERBUFFER_RED_SIZE";
        case GL_RENDERBUFFER_GREEN_SIZE : return "GL_RENDERBUFFER_GREEN_SIZE";
        case GL_RENDERBUFFER_BLUE_SIZE : return "GL_RENDERBUFFER_BLUE_SIZE";
        case GL_RENDERBUFFER_ALPHA_SIZE : return "GL_RENDERBUFFER_ALPHA_SIZE";
        case GL_RENDERBUFFER_DEPTH_SIZE : return "GL_RENDERBUFFER_DEPTH_SIZE";
        case GL_RENDERBUFFER_STENCIL_SIZE : return "GL_RENDERBUFFER_STENCIL_SIZE";

        case GL_FRAMEBUFFER_INCOMPLETE_MULTISAMPLE : return "GL_FRAMEBUFFER_INCOMPLETE_MULTISAMPLE";

        case GL_MAX_SAMPLES : return "GL_MAX_SAMPLES";

        case GL_INDEX : return "GL_INDEX";

        case GL_TEXTURE_LUMINANCE_TYPE : return "GL_TEXTURE_LUMINANCE_TYPE";
        case GL_TEXTURE_INTENSITY_TYPE : return "GL_TEXTURE_INTENSITY_TYPE";

        case GL_FRAMEBUFFER_SRGB : return "GL_FRAMEBUFFER_SRGB";

        case GL_HALF_FLOAT : return "GL_HALF_FLOAT";

            // case GL_MAP_READ_BIT <=> case GL_TRUE
            // case GL_MAP_WRITE_BIT <=> case GL_LINE_LOOP
            // case GL_MAP_INVALIDATE_RANGE_BIT <=> case GL_TRIANGLES
            // case GL_MAP_INVALIDATE_BUFFER_BIT <=> case GL_POLYGON_BIT
            // case GL_MAP_FLUSH_EXPLICIT_BIT <=> case GL_POLYGON_STIPPLE_BIT
            // case GL_MAP_UNSYNCHRONIZED_BIT <=> case GL_PIXEL_MODE_BIT

        case GL_COMPRESSED_RED_RGTC1 : return "GL_COMPRESSED_RED_RGTC1";
        case GL_COMPRESSED_SIGNED_RED_RGTC1 : return "GL_COMPRESSED_SIGNED_RED_RGTC1";
        case GL_COMPRESSED_RG_RGTC2 : return "GL_COMPRESSED_RG_RGTC2";
        case GL_COMPRESSED_SIGNED_RG_RGTC2 : return "GL_COMPRESSED_SIGNED_RG_RGTC2";

        case GL_RG : return "GL_RG";
        case GL_RG_INTEGER : return "GL_RG_INTEGER";
        case GL_R8 : return "GL_R8";
        case GL_R16 : return "GL_R16";
        case GL_RG8 : return "GL_RG8";
        case GL_RG16 : return "GL_RG16";
        case GL_R16F : return "GL_R16F";
        case GL_R32F : return "GL_R32F";
        case GL_RG16F : return "GL_RG16F";
        case GL_RG32F : return "GL_RG32F";
        case GL_R8I : return "GL_R8I";
        case GL_R8UI : return "GL_R8UI";
        case GL_R16I : return "GL_R16I";
        case GL_R16UI : return "GL_R16UI";
        case GL_R32I : return "GL_R32I";
        case GL_R32UI : return "GL_R32UI";
        case GL_RG8I : return "GL_RG8I";
        case GL_RG8UI : return "GL_RG8UI";
        case GL_RG16I : return "GL_RG16I";
        case GL_RG16UI : return "GL_RG16UI";
        case GL_RG32I : return "GL_RG32I";
        case GL_RG32UI : return "GL_RG32UI";

        case GL_VERTEX_ARRAY_BINDING : return "GL_VERTEX_ARRAY_BINDING";
        case GL_CLAMP_VERTEX_COLOR : return "GL_CLAMP_VERTEX_COLOR";
        case GL_CLAMP_FRAGMENT_COLOR : return "GL_CLAMP_FRAGMENT_COLOR";

        case GL_ALPHA_INTEGER : return "GL_ALPHA_INTEGER";

        case GL_SAMPLER_2D_RECT : return "GL_SAMPLER_2D_RECT";
        case GL_SAMPLER_2D_RECT_SHADOW : return "GL_SAMPLER_2D_RECT_SHADOW";
        case GL_SAMPLER_BUFFER : return "GL_SAMPLER_BUFFER";

        case GL_INT_SAMPLER_2D_RECT : return "GL_INT_SAMPLER_2D_RECT";
        case GL_INT_SAMPLER_BUFFER : return "GL_INT_SAMPLER_BUFFER";

        case GL_UNSIGNED_INT_SAMPLER_2D_RECT : return "GL_UNSIGNED_INT_SAMPLER_2D_RECT";
        case GL_UNSIGNED_INT_SAMPLER_BUFFER : return "GL_UNSIGNED_INT_SAMPLER_BUFFER";

        case GL_TEXTURE_BUFFER : return "GL_TEXTURE_BUFFER";
        case GL_MAX_TEXTURE_BUFFER_SIZE : return "GL_MAX_TEXTURE_BUFFER_SIZE";
        case GL_TEXTURE_BINDING_BUFFER : return "GL_TEXTURE_BINDING_BUFFER";
        case GL_TEXTURE_BUFFER_DATA_STORE_BINDING : return "GL_TEXTURE_BUFFER_DATA_STORE_BINDING";
        case GL_TEXTURE_RECTANGLE : return "GL_TEXTURE_RECTANGLE";
        case GL_TEXTURE_BINDING_RECTANGLE : return "GL_TEXTURE_BINDING_RECTANGLE";
        case GL_PROXY_TEXTURE_RECTANGLE : return "GL_PROXY_TEXTURE_RECTANGLE";
        case GL_MAX_RECTANGLE_TEXTURE_SIZE : return "GL_MAX_RECTANGLE_TEXTURE_SIZE";

        case GL_R8_SNORM : return "GL_R8_SNORM";
        case GL_RG8_SNORM : return "GL_RG8_SNORM";
        case GL_RGB8_SNORM : return "GL_RGB8_SNORM";
        case GL_RGBA8_SNORM : return "GL_RGBA8_SNORM";
        case GL_R16_SNORM : return "GL_R16_SNORM";
        case GL_RG16_SNORM : return "GL_RG16_SNORM";
        case GL_RGB16_SNORM : return "GL_RGB16_SNORM";
        case GL_RGBA16_SNORM : return "GL_RGBA16_SNORM";

        case GL_SIGNED_NORMALIZED : return "GL_SIGNED_NORMALIZED";
        case GL_PRIMITIVE_RESTART : return "GL_PRIMITIVE_RESTART";
        case GL_PRIMITIVE_RESTART_INDEX : return "GL_PRIMITIVE_RESTART_INDEX";

        case GL_COPY_READ_BUFFER : return "GL_COPY_READ_BUFFER";
        case GL_COPY_WRITE_BUFFER : return "GL_COPY_WRITE_BUFFER";

        case GL_UNIFORM_BUFFER : return "GL_UNIFORM_BUFFER";
        case GL_UNIFORM_BUFFER_BINDING : return "GL_UNIFORM_BUFFER_BINDING";
        case GL_UNIFORM_BUFFER_START : return "GL_UNIFORM_BUFFER_START";
        case GL_UNIFORM_BUFFER_SIZE : return "GL_UNIFORM_BUFFER_SIZE";

        case GL_MAX_VERTEX_UNIFORM_BLOCKS : return "GL_MAX_VERTEX_UNIFORM_BLOCKS";
        case GL_MAX_GEOMETRY_UNIFORM_BLOCKS : return "GL_MAX_GEOMETRY_UNIFORM_BLOCKS";
        case GL_MAX_FRAGMENT_UNIFORM_BLOCKS : return "GL_MAX_FRAGMENT_UNIFORM_BLOCKS";
        case GL_MAX_COMBINED_UNIFORM_BLOCKS : return "GL_MAX_COMBINED_UNIFORM_BLOCKS";
        case GL_MAX_UNIFORM_BUFFER_BINDINGS : return "GL_MAX_UNIFORM_BUFFER_BINDINGS";
        case GL_MAX_UNIFORM_BLOCK_SIZE : return "GL_MAX_UNIFORM_BLOCK_SIZE";
        case GL_MAX_COMBINED_VERTEX_UNIFORM_COMPONENTS : return "GL_MAX_COMBINED_VERTEX_UNIFORM_COMPONENTS";
        case GL_MAX_COMBINED_GEOMETRY_UNIFORM_COMPONENTS : return "GL_MAX_COMBINED_GEOMETRY_UNIFORM_COMPONENTS";
        case GL_MAX_COMBINED_FRAGMENT_UNIFORM_COMPONENTS : return "GL_MAX_COMBINED_FRAGMENT_UNIFORM_COMPONENTS";

        case GL_UNIFORM_BUFFER_OFFSET_ALIGNMENT : return "GL_UNIFORM_BUFFER_OFFSET_ALIGNMENT";

        case GL_ACTIVE_UNIFORM_BLOCK_MAX_NAME_LENGTH : return "GL_ACTIVE_UNIFORM_BLOCK_MAX_NAME_LENGTH";
        case GL_ACTIVE_UNIFORM_BLOCKS : return "GL_ACTIVE_UNIFORM_BLOCKS";

        case GL_UNIFORM_TYPE : return "GL_UNIFORM_TYPE";
        case GL_UNIFORM_SIZE : return "GL_UNIFORM_SIZE";
        case GL_UNIFORM_NAME_LENGTH : return "GL_UNIFORM_NAME_LENGTH";
        case GL_UNIFORM_BLOCK_INDEX : return "GL_UNIFORM_BLOCK_INDEX";
        case GL_UNIFORM_OFFSET : return "GL_UNIFORM_OFFSET";
        case GL_UNIFORM_ARRAY_STRIDE : return "GL_UNIFORM_ARRAY_STRIDE";
        case GL_UNIFORM_MATRIX_STRIDE : return "GL_UNIFORM_MATRIX_STRIDE";

        case GL_UNIFORM_IS_ROW_MAJOR : return "GL_UNIFORM_IS_ROW_MAJOR";
        case GL_UNIFORM_BLOCK_BINDING : return "GL_UNIFORM_BLOCK_BINDING";
        case GL_UNIFORM_BLOCK_DATA_SIZE : return "GL_UNIFORM_BLOCK_DATA_SIZE";
        case GL_UNIFORM_BLOCK_NAME_LENGTH : return "GL_UNIFORM_BLOCK_NAME_LENGTH";
        case GL_UNIFORM_BLOCK_ACTIVE_UNIFORMS : return "GL_UNIFORM_BLOCK_ACTIVE_UNIFORMS";
        case GL_UNIFORM_BLOCK_ACTIVE_UNIFORM_INDICES : return "GL_UNIFORM_BLOCK_ACTIVE_UNIFORM_INDICES";
        case GL_UNIFORM_BLOCK_REFERENCED_BY_VERTEX_SHADER : return "GL_UNIFORM_BLOCK_REFERENCED_BY_VERTEX_SHADER";
        case GL_UNIFORM_BLOCK_REFERENCED_BY_GEOMETRY_SHADER : return "GL_UNIFORM_BLOCK_REFERENCED_BY_GEOMETRY_SHADER";
        case GL_UNIFORM_BLOCK_REFERENCED_BY_FRAGMENT_SHADER : return "GL_UNIFORM_BLOCK_REFERENCED_BY_FRAGMENT_SHADER";

            // case GL_INVALID_INDEX <=> case GL_ALL_ATTRIB_BITS
            // case GL_CONTEXT_CORE_PROFILE_BIT <=> case GL_TRUE
            // case GL_CONTEXT_COMPATIBILITY_PROFILE_BIT <=> case GL_LINE_LOOP

        case GL_LINES_ADJACENCY : return "GL_LINES_ADJACENCY";
        case GL_LINE_STRIP_ADJACENCY : return "GL_LINE_STRIP_ADJACENCY";
        case GL_TRIANGLES_ADJACENCY : return "GL_TRIANGLES_ADJACENCY";
        case GL_TRIANGLE_STRIP_ADJACENCY : return "GL_TRIANGLE_STRIP_ADJACENCY";

            // case GL_PROGRAM_POINT_SIZE <=> case GL_VERTEX_PROGRAM_POINT_SIZE

        case GL_MAX_GEOMETRY_TEXTURE_IMAGE_UNITS : return "GL_MAX_GEOMETRY_TEXTURE_IMAGE_UNITS";

        case GL_FRAMEBUFFER_ATTACHMENT_LAYERED : return "GL_FRAMEBUFFER_ATTACHMENT_LAYERED";
        case GL_FRAMEBUFFER_INCOMPLETE_LAYER_TARGETS : return "GL_FRAMEBUFFER_INCOMPLETE_LAYER_TARGETS";

        case GL_GEOMETRY_VERTICES_OUT : return "GL_GEOMETRY_VERTICES_OUT";
        case GL_GEOMETRY_INPUT_TYPE : return "GL_GEOMETRY_INPUT_TYPE";
        case GL_GEOMETRY_OUTPUT_TYPE : return "GL_GEOMETRY_OUTPUT_TYPE";
        case GL_MAX_GEOMETRY_UNIFORM_COMPONENTS : return "GL_MAX_GEOMETRY_UNIFORM_COMPONENTS";

        case GL_MAX_GEOMETRY_OUTPUT_VERTICES : return "GL_MAX_GEOMETRY_OUTPUT_VERTICES";
        case GL_MAX_GEOMETRY_TOTAL_OUTPUT_COMPONENTS : return "GL_MAX_GEOMETRY_TOTAL_OUTPUT_COMPONENTS";
        case GL_MAX_VERTEX_OUTPUT_COMPONENTS : return "GL_MAX_VERTEX_OUTPUT_COMPONENTS";
        case GL_MAX_GEOMETRY_INPUT_COMPONENTS : return "GL_MAX_GEOMETRY_INPUT_COMPONENTS";
        case GL_MAX_GEOMETRY_OUTPUT_COMPONENTS : return "GL_MAX_GEOMETRY_OUTPUT_COMPONENTS";
        case GL_MAX_FRAGMENT_INPUT_COMPONENTS : return "GL_MAX_FRAGMENT_INPUT_COMPONENTS";

        case GL_CONTEXT_PROFILE_MASK : return "GL_CONTEXT_PROFILE_MASK";

        case GL_DEPTH_CLAMP : return "GL_DEPTH_CLAMP";

        case GL_QUADS_FOLLOW_PROVOKING_VERTEX_CONVENTION : return "GL_QUADS_FOLLOW_PROVOKING_VERTEX_CONVENTION";
        case GL_FIRST_VERTEX_CONVENTION : return "GL_FIRST_VERTEX_CONVENTION";
        case GL_LAST_VERTEX_CONVENTION : return "GL_LAST_VERTEX_CONVENTION";

        case GL_PROVOKING_VERTEX : return "GL_PROVOKING_VERTEX";

        case GL_TEXTURE_CUBE_MAP_SEAMLESS : return "GL_TEXTURE_CUBE_MAP_SEAMLESS";

        case GL_MAX_SERVER_WAIT_TIMEOUT : return "GL_MAX_SERVER_WAIT_TIMEOUT";

        case GL_OBJECT_TYPE : return "GL_OBJECT_TYPE";

        case GL_SYNC_CONDITION : return "GL_SYNC_CONDITION";
        case GL_SYNC_STATUS : return "GL_SYNC_STATUS";
        case GL_SYNC_FLAGS : return "GL_SYNC_FLAGS";
        case GL_SYNC_FENCE : return "GL_SYNC_FENCE";

        case GL_SYNC_GPU_COMMANDS_COMPLETE : return "GL_SYNC_GPU_COMMANDS_COMPLETE";

        case GL_UNSIGNALED : return "GL_UNSIGNALED";
        case GL_SIGNALED : return "GL_SIGNALED";

        case GL_ALREADY_SIGNALED : return "GL_ALREADY_SIGNALED";

        case GL_TIMEOUT_EXPIRED : return "GL_TIMEOUT_EXPIRED";

        case GL_CONDITION_SATISFIED : return "GL_CONDITION_SATISFIED";

        case GL_WAIT_FAILED : return "GL_WAIT_FAILED";
            // case GL_TIMEOUT_IGNORED : return "GL_TIMEOUT_IGNORED";

            // case GL_SYNC_FLUSH_COMMANDS_BIT <=> case GL_TRUE
        case GL_SAMPLE_POSITION : return "GL_SAMPLE_POSITION";

        case GL_SAMPLE_MASK : return "GL_SAMPLE_MASK";
        case GL_SAMPLE_MASK_VALUE : return "GL_SAMPLE_MASK_VALUE";
        case GL_MAX_SAMPLE_MASK_WORDS : return "GL_MAX_SAMPLE_MASK_WORDS";

        case GL_TEXTURE_2D_MULTISAMPLE : return "GL_TEXTURE_2D_MULTISAMPLE";
        case GL_PROXY_TEXTURE_2D_MULTISAMPLE : return "GL_PROXY_TEXTURE_2D_MULTISAMPLE";
        case GL_TEXTURE_2D_MULTISAMPLE_ARRAY : return "GL_TEXTURE_2D_MULTISAMPLE_ARRAY";
        case GL_PROXY_TEXTURE_2D_MULTISAMPLE_ARRAY : return "GL_PROXY_TEXTURE_2D_MULTISAMPLE_ARRAY";
        case GL_TEXTURE_BINDING_2D_MULTISAMPLE : return "GL_TEXTURE_BINDING_2D_MULTISAMPLE";
        case GL_TEXTURE_BINDING_2D_MULTISAMPLE_ARRAY : return "GL_TEXTURE_BINDING_2D_MULTISAMPLE_ARRAY";
        case GL_TEXTURE_SAMPLES : return "GL_TEXTURE_SAMPLES";
        case GL_TEXTURE_FIXED_SAMPLE_LOCATIONS : return "GL_TEXTURE_FIXED_SAMPLE_LOCATIONS";

        case GL_SAMPLER_2D_MULTISAMPLE : return "GL_SAMPLER_2D_MULTISAMPLE";
        case GL_INT_SAMPLER_2D_MULTISAMPLE : return "GL_INT_SAMPLER_2D_MULTISAMPLE";
        case GL_UNSIGNED_INT_SAMPLER_2D_MULTISAMPLE : return "GL_UNSIGNED_INT_SAMPLER_2D_MULTISAMPLE";
        case GL_SAMPLER_2D_MULTISAMPLE_ARRAY : return "GL_SAMPLER_2D_MULTISAMPLE_ARRAY";
        case GL_INT_SAMPLER_2D_MULTISAMPLE_ARRAY : return "GL_INT_SAMPLER_2D_MULTISAMPLE_ARRAY";
        case GL_UNSIGNED_INT_SAMPLER_2D_MULTISAMPLE_ARRAY : return "GL_UNSIGNED_INT_SAMPLER_2D_MULTISAMPLE_ARRAY";

        case GL_MAX_COLOR_TEXTURE_SAMPLES : return "GL_MAX_COLOR_TEXTURE_SAMPLES";
        case GL_MAX_DEPTH_TEXTURE_SAMPLES : return "GL_MAX_DEPTH_TEXTURE_SAMPLES";
        case GL_MAX_INTEGER_SAMPLES : return "GL_MAX_INTEGER_SAMPLES";

        case GL_VERTEX_ATTRIB_ARRAY_DIVISOR : return "GL_VERTEX_ATTRIB_ARRAY_DIVISOR";

        case GL_SRC1_COLOR : return "GL_SRC1_COLOR";
        case GL_ONE_MINUS_SRC1_COLOR : return "GL_ONE_MINUS_SRC1_COLOR";
        case GL_ONE_MINUS_SRC1_ALPHA : return "GL_ONE_MINUS_SRC1_ALPHA";

        case GL_MAX_DUAL_SOURCE_DRAW_BUFFERS : return "GL_MAX_DUAL_SOURCE_DRAW_BUFFERS";

        case GL_ANY_SAMPLES_PASSED : return "GL_ANY_SAMPLES_PASSED";

        case GL_SAMPLER_BINDING : return "GL_SAMPLER_BINDING";

        case GL_RGB10_A2UI : return "GL_RGB10_A2UI";

        case GL_TEXTURE_SWIZZLE_R : return "GL_TEXTURE_SWIZZLE_R";
        case GL_TEXTURE_SWIZZLE_G : return "GL_TEXTURE_SWIZZLE_G";
        case GL_TEXTURE_SWIZZLE_B : return "GL_TEXTURE_SWIZZLE_B";
        case GL_TEXTURE_SWIZZLE_A : return "GL_TEXTURE_SWIZZLE_A";
        case GL_TEXTURE_SWIZZLE_RGBA : return "GL_TEXTURE_SWIZZLE_RGBA";

        case GL_TIME_ELAPSED : return "GL_TIME_ELAPSED";
        case GL_TIMESTAMP : return "GL_TIMESTAMP";

        case GL_INT_2_10_10_10_REV : return "GL_INT_2_10_10_10_REV";

        default :
            throw std::invalid_argument("La macro n'a pas été trouvée.");
    }
}
