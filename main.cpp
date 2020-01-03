
#include "igl/opengl/glfw/renderer.h"
#include "tutorial/sandBox/inputManager.h"
#include "igl/opengl/ViewerData.h"

int main(int argc, char *argv[])
{
  Display *disp = new Display(1000, 800, "Wellcome");
  Renderer renderer;
  igl::opengl::glfw::Viewer viewer;
  viewer.load_mesh_from_file("C:/Dev/EngineIGLnew/tutorial/data/sphere.obj");

 
  int arms = 4;
  for (int i = 0; i < arms; i++) {
	  viewer.load_mesh_from_file("C:/Dev/EngineIGLnew/tutorial/data/yCylinder.obj");
  }



  Init(*disp);
  renderer.init(&viewer);
  for (int i = 0; i <= arms; i++) {
	  viewer.selected_data_index = i;
	  viewer.data().set_colors(Eigen::RowVector3d(0.7, 0.7, 0));
	  viewer.data().set_face_based(!viewer.data().face_based);
	  renderer.core().toggle(viewer.data().show_lines);
  }
  viewer.init_ik(arms);
  disp->SetRenderer(&renderer);
  disp->launch_rendering(true);
  
  delete disp;
}
