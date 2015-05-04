
#include "create_vao.h"

#include <bd/graphics/quad.h> 

#include <glm/glm.hpp>


namespace {
    const float VOL_MIN = -0.5f;
    const float VOL_MAX =  0.5f;
}


///////////////////////////////////////////////////////////////////////////////
float sliceIndexToWorldPos(unsigned idx, float start, float delta)
{
    return start + delta*idx;
}


///////////////////////////////////////////////////////////////////////////////
glm::u16vec4 sliceIndexToElements(uint16_t idx)
{
    const uint16_t stride = 4;
    return glm::u16vec4(0, 1, 3, 2) + uint16_t(stride*idx);
}


///////////////////////////////////////////////////////////////////////////////
float start(size_t num_slices, float min, float max)
{
 //   float span = std::abs(max - min);
 //   float s = -1.0f * delta(num_slices, min, max) * (num_slices / 2);

    return num_slices > 1 ? min : 0.0f;
}


///////////////////////////////////////////////////////////////////////////////
float delta(size_t num_slices, float min, float max)
{
    if (num_slices <= 1) {
        return 0.0f;
    }

    return (max - min) / (num_slices-1);
}

///////////////////////////////////////////////////////////////////////////////
void create_verts_xy(size_t numSlices, std::vector<glm::vec4> &vbuf)
{
    float st = start(numSlices, VOL_MIN, VOL_MAX);
    float del = delta(numSlices, VOL_MIN, VOL_MAX);
    size_t numVerts = numSlices * bd::Quad::vert_element_size;

    vbuf.resize(numVerts);

    std::vector<glm::vec4>::iterator vbufIter{ vbuf.begin() };
    for (int i = 0; i < numSlices; ++i) {
        float pos{ sliceIndexToWorldPos(i, st, del) };
        std::array<glm::vec4, 4> verts(bd::Quad::verts_xy);
        std::for_each(verts.begin(), verts.end(), [pos](glm::vec4 &vv){ vv.z = pos; });
        std::copy(verts.begin(), verts.end(), vbufIter);
        vbufIter += verts.size();
    }
}


///////////////////////////////////////////////////////////////////////////////
void create_verts_xz(size_t numSlices, std::vector<glm::vec4> &vbuf)
{
    float st = start(numSlices, VOL_MIN, VOL_MAX);
    float del = delta(numSlices, VOL_MIN, VOL_MAX);
    size_t numVerts = numSlices * bd::Quad::vert_element_size;

    vbuf.resize(numVerts);

    std::vector<glm::vec4>::iterator vbufIter{ vbuf.begin() };
    for (int i = 0; i < numSlices; ++i) {
        float pos{ sliceIndexToWorldPos(i, st, del) };
        std::array<glm::vec4, 4> verts(bd::Quad::verts_xz);
        std::for_each(verts.begin(), verts.end(), [pos](glm::vec4 &vv){ vv.y = pos; });
        std::copy(verts.begin(), verts.end(), vbufIter);
        vbufIter += verts.size();
    }
}


///////////////////////////////////////////////////////////////////////////////
void create_verts_yz(size_t numSlices, std::vector<glm::vec4> &vbuf)
{
    float st = start(numSlices, VOL_MIN, VOL_MAX);
    float del = delta(numSlices, VOL_MIN, VOL_MAX);
    size_t numVerts = numSlices * bd::Quad::vert_element_size;

    vbuf.resize(numVerts);

    std::vector<glm::vec4>::iterator vbufIter{ vbuf.begin() };
    for (int i = 0; i < numSlices; ++i) {
        float pos{ sliceIndexToWorldPos(i, st, del) };
        std::array<glm::vec4, 4> verts(bd::Quad::verts_yz);
        std::for_each(verts.begin(), verts.end(), [pos](glm::vec4 &vv){ vv.x = pos; });
        std::copy(verts.begin(), verts.end(), vbufIter);
        vbufIter += verts.size();
    }
}


///////////////////////////////////////////////////////////////////////////////
void create_texbuf_xy(size_t numSlices, std::vector<glm::vec4> &texbuf)
{
    create_verts_xy(numSlices, texbuf);

    //TODO: float diff = 1-VOL_MAX doesn't work for all negative VOL_MAXes.
    float diff = 1 - VOL_MAX;
    std::for_each(texbuf.begin(), texbuf.end(), 
        [diff](glm::vec4 &v){ v += glm::vec4(diff, diff, diff, 0.0f); });
}


///////////////////////////////////////////////////////////////////////////////
void create_texbuf_xz(size_t numSlices, std::vector<glm::vec4> &texbuf)
{
    create_verts_xz(numSlices, texbuf);

    //TODO: float diff = 1-VOL_MAX doesn't work for all negative VOL_MAXes.
    float diff = 1 - VOL_MAX;
    std::for_each(texbuf.begin(), texbuf.end(), 
        [diff](glm::vec4 &v){ v += glm::vec4(diff, diff, diff, 0.0f); });
}


///////////////////////////////////////////////////////////////////////////////
void create_texbuf_yz(size_t numSlices, std::vector<glm::vec4> &texbuf)
{
    create_verts_yz(numSlices, texbuf);

    //TODO: float diff = 1-VOL_MAX doesn't work for all negative VOL_MAXes.
    float diff = 1 - VOL_MAX;
    std::for_each(texbuf.begin(), texbuf.end(), 
        [diff](glm::vec4 &v){ v += glm::vec4(diff, diff, diff, 0.0f); });
}


///////////////////////////////////////////////////////////////////////////////
void create_elementIndices(size_t numSlices, std::vector<uint16_t> &elebuf)
{
    elebuf.resize(numSlices*5);
    auto it = elebuf.begin();
    auto end = elebuf.end();
    for (int i=0; it != end; it+=5, ++i){
        *it     = uint16_t(0 + 4*i);
        *(it+1) = uint16_t(1 + 4*i);
        *(it+2) = uint16_t(3 + 4*i);
        *(it+3) = uint16_t(2 + 4*i);
        *(it+4) = uint16_t(0xFFFF);  // Special restart symbol.
    }


//    for (int i = 0; i < elebuf.size(); i++) {
//        elebuf.push_back(uint16_t(0 + 4*i));
//        elebuf.push_back(uint16_t(1 + 4*i));
//        elebuf.push_back(uint16_t(3 + 4*i));
//        elebuf.push_back(uint16_t(2 + 4*i));
//        elebuf.push_back(uint16_t(0xFFFF));  // Special restart symbol.
//    }
     

//    std::generate(elebuf.begin(), elebuf.end(), 
//        [&i](){ auto rval = sliceIndexToElements(i); ++i; return rval; });
}

//int create_xy(size_t numSlices, std::vector<glm::vec4> &vbuf,
//    std::vector<glm::vec3> &texbuf, std::vector<glm::u16vec4> &elebuf, int eleIdxContinuation)
//{
//    int eleIdx = eleIdxContinuation;
//    float st = start(numSlices, -0.5f, 0.5f);
//    float delt = delta(numSlices, st, -1.0f * st);
//	for (unsigned int i = 0; i < numSlices; ++i) {
//		float pos = sliceIndexToWorldPos(i, st, delt);
//		for (glm::vec4 vert : bd::Quad::verts_xy) {
//			vert.z = pos;    // adjust along Z-axis
//			vbuf.push_back(vert);
//		}
//        for (glm::vec3 coord : bd::Quad::texcoords_xy) {
//            coord.z = pos;
//            texbuf.push_back(coord);
//        }
//        elebuf.push_back(sliceIndexToElements(eleIdx));
//        eleIdx += 4;
//	}
//
//    return eleIdx;
//}
//
//int create_xz(size_t numSlices, std::vector<glm::vec4> &vbuf,
//    std::vector<glm::vec3> &texbuf, std::vector<glm::u16vec4> &elebuf,
//    int eleIdxContinuation)
//{
//    int eleIdx = eleIdxContinuation;
//    float st = start(numSlices, -0.5f, 0.5f);
//    float delt = delta(numSlices, st, -1.0f * st);
//    for (unsigned int i = 0; i < numSlices; ++i) {
//        float pos = sliceIndexToWorldPos(i, st, delt);
//        for (glm::vec4 vert : bd::Quad::verts_xz) {
//            vert.y = pos;    // adjust along Y-axis
//            vbuf.push_back(vert);
//        }
//        for (glm::vec3 coord : bd::Quad::texcoords_xz) {
//            coord.y = pos;
//            texbuf.push_back(coord);
//        }
//        elebuf.push_back(sliceIndexToElements(eleIdx));
//        eleIdx += 4;
//    }
//
//    return eleIdx;
//}
//
//int create_yz(size_t numSlices, std::vector<glm::vec4> &vbuf,
//    std::vector<glm::vec3> &texbuf, std::vector<glm::u16vec4> &elebuf,
//    int eleIdxContinuation)
//{
//    int eleIdx = eleIdxContinuation;
//    float st = start(numSlices, -0.5f, 0.5f);
//    float delt = delta(numSlices, st, -1.0f * st);
//    for (unsigned int i = 0; i < numSlices; ++i) {
//        float pos = sliceIndexToWorldPos(i, st, delt);
//        for (glm::vec4 vert : bd::Quad::verts_yz) {
//            vert.x = pos;    // adjust along X-axis
//            vbuf.push_back(vert);
//        }
//        for (glm::vec3 coord : bd::Quad::texcoords_yz) {
//            coord.x = pos;
//            texbuf.push_back(coord);
//        }
//        elebuf.push_back(sliceIndexToElements(eleIdx));
//        eleIdx += 4;
//    }
//
//    return eleIdx;
//
//
//}