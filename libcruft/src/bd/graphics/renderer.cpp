//
// Created by Jim Pelton on 8/1/16.
//

#include <GL/glew.h>
#include <bd/graphics/renderer.h>
//#include "constants.h"

#include <bd/log/logger.h>

#define _USE_MATH_DEFINES
#include <math.h>

namespace bd
{



Renderer::Renderer()
    : m_viewPortXPos{ 0 }
    , m_viewPortYPos{ 0 }
    , m_viewPortWidth{ 640 }
    , m_viewPortHeight{ 480 }
    , m_aspectRatio{ m_viewPortWidth / (float)m_viewPortHeight }
    , m_near{ 0.01f }
    , m_far{ 10000.0f }
    , m_fov{ 50.0f }
    , m_focalLength{ 0 }
    , m_worldMat{ 1.0f }
    , m_viewMat{ 1.0f }
    , m_projMat{ 1.0f }
    , m_wvpMat{ 1.0f }
    , m_camera{ }
{
  bd::Dbg() << "Default renderer created.";
  // resize(m_viewPortWidth, m_viewPortHeight);
  m_focalLength = 1.0f / std::tan(M_PI / 180.0f * m_fov / 2.0f);
}


Renderer::~Renderer()
{
}


void
Renderer::resize(unsigned int w, unsigned int h)
{
  m_viewPortXPos = 0;
  m_viewPortYPos = 0;
  m_viewPortWidth = w;
  m_viewPortHeight = h;
  m_aspectRatio = w / static_cast<float>(h);
  glViewport(0, 0, w, h);

//  setViewMatrix(I4x4);
//  setWorldMatrix(I4x4);

  updateProjectionMatrix();

  bd::Dbg() << "Resized render viewport: " << w << "X" << h;


}

unsigned int
Renderer::getViewPortWidth() const
{
  return m_viewPortWidth;
}


unsigned int
Renderer::getViewPortHeight() const
{
  return m_viewPortHeight;
}


float
Renderer::getAspectRatio() const
{
  return m_aspectRatio;
}

void
Renderer::setFov(float fov)
{
  m_fov = fov;

  m_focalLength = 1.0f / std::tan(M_PI / 180.0f * fov / 2.0f);

  updateProjectionMatrix();
}


float
Renderer::getFov() const
{
  return m_fov;
}


float
Renderer::getFocalLength() const
{
  return m_focalLength;
}


void
Renderer::setWorldMatrix(glm::mat4 const &world)
{
  m_worldMat = world;
  m_wvpMat = m_projMat * m_viewMat * m_worldMat;
}


void
Renderer::setViewMatrix(glm::mat4 const &view)
{
  m_viewMat = view;
  m_wvpMat = m_projMat * m_viewMat * m_worldMat;

}


void
Renderer::setProjectionMatrix(glm::mat4 const &proj)
{
  m_projMat = proj;
  m_wvpMat = m_projMat * m_viewMat * m_worldMat;
}


glm::mat4 const &
Renderer::getWorldMatrix() const
{
  return m_worldMat;
}


glm::mat4 const &
Renderer::getViewMatrix() const
{
  return m_viewMat;
}


glm::mat4 const &
Renderer::getProjectionMatrix() const
{
  return m_projMat;
}


glm::mat4 const &
Renderer::getWorldViewProjectionMatrix() const
{
  return m_wvpMat;
}


Camera const &
Renderer::getCamera() const
{
  return m_camera;
}


Camera &
Renderer::getCamera()
{
  return m_camera;
}


void
Renderer::updateProjectionMatrix()
{
  setProjectionMatrix(
      glm::perspectiveRH(glm::radians(m_fov),
                         m_viewPortWidth / float(m_viewPortHeight),
                         m_near,
                         m_far));
}


} // namespace subvol
