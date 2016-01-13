//
// Created by jim on 10/22/15.
//

#ifndef volumerenderer_h__
#define volumerenderer_h__

#include "sliceset.h"

#include <GL/glew.h>
#include <GLFW/glfw3.h>

#include <bd/graphics/view.h>
#include <bd/graphics/shader.h>
#include <bd/graphics/texture.h>
#include <bd/volume/blockcollection.h>
#include <bd/graphics/vertexarrayobject.h>

#include <glm/fwd.hpp>

#include <memory>


class BlockRenderer {

public:
  BlockRenderer();


  //////////////////////////////////////////////////////////////////////////////
  BlockRenderer(std::shared_ptr<bd::ShaderProgram> volumeShader,
                std::shared_ptr<bd::ShaderProgram> wireframeShader,
                std::shared_ptr<bd::BlockCollection> blockCollection,
                std::shared_ptr<bd::Texture> tfuncTexture,
                std::shared_ptr<bd::VertexArrayObject> blocksVAO,
                std::shared_ptr<bd::VertexArrayObject> bboxVAO);

  //////////////////////////////////////////////////////////////////////////////
  virtual ~BlockRenderer();


  //////////////////////////////////////////////////////////////////////////////
  //virtual void renderSingleFrame();


  //////////////////////////////////////////////////////////////////////////////
  /// \brief Draw each non-empty block.
  //////////////////////////////////////////////////////////////////////////////
  void drawNonEmptyBlocks();


  //////////////////////////////////////////////////////////////////////////////
  /// \brief Draw wireframe bounding boxes around the blocks.
  //////////////////////////////////////////////////////////////////////////////
  void drawNonEmptyBoundingBoxes();

  //////////////////////////////////////////////////////////////////////////////
  bool init();


  //////////////////////////////////////////////////////////////////////////////
  void setTfuncScaleValue(float val);


  //////////////////////////////////////////////////////////////////////////////
  void setViewMatrix(const glm::mat4 &);


  //////////////////////////////////////////////////////////////////////////////
  void setNumSlices(int n);

private:


  //////////////////////////////////////////////////////////////////////////////
  /// \brief Disable GL_DEPTH_TEST and draw transparent slices
  //////////////////////////////////////////////////////////////////////////////
  void drawSlices(int baseVertex);


  //////////////////////////////////////////////////////////////////////////////
  /// \brief Loop through the blocks and draw each one
  //////////////////////////////////////////////////////////////////////////////
  void drawNonEmptyBlocks_Forward();


  //////////////////////////////////////////////////////////////////////////////
  /// \brief Determine the viewing direction and draw the blocks in proper order.
  //////////////////////////////////////////////////////////////////////////////


  //////////////////////////////////////////////////////////////////////////////
  /// \brief Compute the base vertex offset for the slices vertex buffer based
  ///        off the largest component of \c viewdir.
  /////////////////////////////////////////////////////////////////////////////
  int computeBaseVertexFromViewDir(const glm::vec3 &viewdir);

private:

  int m_numSlicesPerBlock;            ///< Number of slices per block
  float m_tfuncScaleValue;            ///< Transfer function scaling value

  glm::mat4 m_viewMatrix;             ///< View matrix for the camera

  SliceSet m_selectedSliceSet;

  std::shared_ptr<bd::ShaderProgram> m_volumeShader;
  std::shared_ptr<bd::ShaderProgram> m_wireframeShader;
  std::shared_ptr<bd::BlockCollection> m_blockCollection;
  std::shared_ptr<bd::Texture> m_tfuncTexture;               ///< Transfer function texture
  std::shared_ptr<bd::VertexArrayObject> m_quadsVao;         ///< Quad geometry verts
  std::shared_ptr<bd::VertexArrayObject> m_boxesVao;         ///< bounding box wireframe verts

};


#endif //volumerenderer_h__