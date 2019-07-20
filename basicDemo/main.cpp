#include <glad/glad.h> // Glad has to be include before glfw
#include <GLFW/glfw3.h>
#include <glm/glm.hpp>
#include <iostream>
#include <stb_image.h>
#include <AntTweakBar.h>

#include "Shader.h"
#include "class/Obj.h"
#include "components/loader.h"
#include "class/CubeMap.h"
#include "class/camera.h"
#include "class/helpers.h"
#include "class/Light/LDir.h"
#include "class/interface.h"

// Window current width
unsigned int windowWidth = 800;
// Window current height
unsigned int windowHeight = 600;
// Window title
const char *windowTitle = "Proyecto";
// Window pointer
GLFWwindow *window;

Camera* camera;

TwInterface* interface;

CubeMap *cubeMap;
std::vector<Obj*> objects;
Obj* object;
DrawParameters drawParameters;

bool pressLeft;
int pressMenu, menuLigth = 1;

void initGui() {
	
	// Create a tweak bar
	interface = new TwInterface(windowWidth, windowHeight,"dirL");

    interface->dirlAmbient = drawParameters.dirLigth->aColor;
	interface->dirlDifuse = drawParameters.dirLigth->dColor;
	interface->dirlSpecular = drawParameters.dirLigth->sColor;
	interface->dirlPosition = drawParameters.dirLigth->direccion;
	interface->dirlVis = drawParameters.dirLigth->active;
}


void updateGui(){

    drawParameters.dirLigth->aColor = interface->dirlAmbient;
	drawParameters.dirLigth->dColor = interface->dirlDifuse;
	drawParameters.dirLigth->sColor = interface->dirlSpecular;
	drawParameters.dirLigth->direccion = interface->dirlPosition;
	drawParameters.dirLigth->active = interface->dirlVis;
}

std::vector<std::string> initCubeMapFaces(){

    std::vector<std::string> faces;
   
    faces.push_back("assets/textures/cubemap/skybox/right.jpg");
    faces.push_back("assets/textures/cubemap/skybox/left.jpg");
    faces.push_back("assets/textures/cubemap/skybox/top.jpg");
    faces.push_back("assets/textures/cubemap/skybox/bottom.jpg");
    faces.push_back("assets/textures/cubemap/skybox/front.jpg");
    faces.push_back("assets/textures/cubemap/skybox/back.jpg");

    return faces;
}

void loadObjects(std::string path, std::string shader){

    object = loadObj(path.c_str(),shader);
	
	if (object == NULL) {

		std::cout << "Error al cargar" << std::endl;
	}
	else {

		objects.push_back(object);

	}

}

void mouse_callback(GLFWwindow* window, double xpos, double ypos);
void onMouseButton(GLFWwindow* window, int button, int action, int mods);
/**
 * Handles the window resize
 * @param{GLFWwindow} window pointer
 * @param{int} new width of the window
 * @param{int} new height of the window
 * */
void resize(GLFWwindow *window, int width, int height)
{
    windowWidth = width;
    windowHeight = height;
    // Sets the OpenGL viewport size and position
    glViewport(0, 0, windowWidth, windowHeight);

    TwWindowSize(width, height);
}
/**
 * Initialize the glfw library
 * @returns{bool} true if everything goes ok
 * */
bool initWindow()
{
    // Initialize glfw
    glfwInit();
    // Sets the Opegl context to Opengl 3.0
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

    // Creates the window
    window = glfwCreateWindow(windowWidth, windowHeight, windowTitle, NULL, NULL);

    // The window couldn't be created
    if (!window)
    {
        std::cout << "Failed to create the glfw window" << std::endl;
        glfwTerminate(); // Stops the glfw program
        return false;
    }

    // Creates the glfwContext, this has to be made before calling initGlad()
    glfwMakeContextCurrent(window);

    // Window resize callback
    glfwSetFramebufferSizeCallback(window, resize);
	glfwSetCursorPosCallback(window, mouse_callback);
	glfwSetMouseButtonCallback(window, onMouseButton);
    return true;
}
/**
 * Initialize the glad library
 * @returns{bool} true if everything goes ok
 * */
bool initGlad()
{
    // Initialize glad
    int status = gladLoadGLLoader((GLADloadproc)glfwGetProcAddress);
    // If something went wrong during the glad initialization
    if (!status)
    {
        std::cout << status << std::endl;
        std::cout << "Failed to initialize GLAD" << std::endl;
        return false;
    }
    return true;
}
/**
 * Initialize the opengl context
 * */
void initGL()
{
    // Enables the z-buffer test
    glEnable(GL_DEPTH_TEST);
    // Sets the ViewPort
    glViewport(0, 0, windowWidth, windowHeight);
    // Sets the clear color
    glClearColor(0.3f, 0.3f, 0.3f, 1.0f);
}

bool init()
{
    // Initialize the window, and the glad components
    if (!initWindow() || !initGlad())
        return false;

    // Initialize the opengl context
    initGL();
	
	camera = new Camera();

	drawParameters.dirLigth = new DirLigth(glm::vec3(1.0f), glm::vec3(1.0f), glm::vec3(1.0f), glm::vec3(-2.0f, -1.0f, -5.0f));

    // Loads the shader
	loadObjects("assets/obj/n/nanosuit.obj","");
	loadObjects("assets/obj/crate/cubito.obj","reflect");
	loadObjects("assets/obj/plane/plane.obj", "");
	loadObjects("assets/obj/plane/plane2.obj", "");

	glm::mat4 trans = glm::mat4(1.0f);
	trans = glm::translate(trans, glm::vec3(-3.0f, -1.0f, 0.0f));
	trans = glm::rotate(trans, glm::radians(0.0f), glm::vec3(0.0, 1.0, 0.0));
	trans = glm::scale(trans, glm::vec3(1.0f));

	objects[1]->model = trans;

	trans = glm::mat4(1.0f);
	trans = glm::translate(trans, glm::vec3(0.0f, 0.0f, 0.0f));
	trans = glm::rotate(trans, glm::radians(90.0f), glm::vec3(0.0, 0.0, 1.0));
	trans = glm::scale(trans, glm::vec3(10.0f));

	objects[2]->model = trans;

	trans = glm::mat4(1.0f);
	trans = glm::translate(trans, glm::vec3(3.0f, 1.0f, 0.0f));
	trans = glm::rotate(trans, glm::radians(90.0f), glm::vec3(0.0, 1.0, 0.0));
	trans = glm::scale(trans, glm::vec3(1.0f));
	objects[3]->model = trans;

	stbi_set_flip_vertically_on_load(false);
    cubeMap = new CubeMap(initCubeMapFaces());
	drawParameters.skyboxTexture = cubeMap->textureId;

    initGui();
    return true;
}
/**
 * Process the keyboard input
 * There are ways of implementing this function through callbacks provide by
 * the GLFW API, check the GLFW documentation to find more
 * @param{GLFWwindow} window pointer
 * */
void processKeyboardInput(GLFWwindow *window)
{
    // Checks if the escape key is pressed
    if (glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS)
        // Tells glfw to close the window as soon as possible
        glfwSetWindowShouldClose(window, true);

    // Checks if the r key is pressed
   /* if (glfwGetKey(window, GLFW_KEY_R) == GLFW_PRESS)
    {
        // Reloads the shader
        delete shader;
        shader = new Shader("assets/shaders/basic.vert", "assets/shaders/basic.frag");
    }
	*/
	// Camera move
	if (glfwGetKey(window, GLFW_KEY_W) == GLFW_PRESS) {

		camera->moveForward();

	}
	if (glfwGetKey(window, GLFW_KEY_S) == GLFW_PRESS) {

		camera->moveBackward();

	}
	if (glfwGetKey(window, GLFW_KEY_A) == GLFW_PRESS) {

		camera->strafeLeft();

	}
	if (glfwGetKey(window, GLFW_KEY_D) == GLFW_PRESS) {

		camera->strafeRight();

	}
    if (glfwGetKey(window, GLFW_KEY_L) == GLFW_PRESS) {

		
		if (menuLigth == 1) {

			TwDefine(" dirL visible=true ");

			menuLigth=2;
		}
		else if(menuLigth == 2){
			

			TwDefine(" dirL visible=false ");
			menuLigth = 1;
		}
	}
}
/**
 * Render Function
 * */
void render()
{
    // Clears the color and depth buffers from the frame buffer
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	glEnable(GL_FRAMEBUFFER_SRGB);
	drawParameters.view = camera->getWorlToViewMatrix();
	drawParameters.viewPos = camera->position;
	drawParameters.projection = glm::perspective(glm::radians(90.0f), (float)windowWidth / (float)windowHeight, 0.1f, 1000.0f);

	for (int i = 0; i < objects.size(); i++) {
		objects[i]->Draw(drawParameters);
	}
	
	glDepthFunc(GL_LEQUAL);
	drawParameters.view = glm::mat4(glm::mat3(camera->getWorlToViewMatrix()));
	cubeMap->Draw(drawParameters);
	glDepthFunc(GL_LESS);

    TwDraw();
	updateGui();

    glfwSwapBuffers(window);
}
/**
 * App main loop
 * */
void update()
{
    // Loop until something tells the window, that it has to be closed
    while (!glfwWindowShouldClose(window))
    {
        // Checks for keyboard inputs
        processKeyboardInput(window);

        // Renders everything
        render();

        // Check and call events
        glfwPollEvents();
    }
}
/**
 * App starting point
 * @param{int} number of arguments
 * @param{char const *[]} running arguments
 * @returns{int} app exit code
 * */
int main(int argc, char const *argv[])
{
    // Initialize all the app components
    if (!init())
    {
        // Something went wrong
        std::cin.ignore();
        return -1;
    }

    std::cout << "=====================================================" << std::endl
              << "        Press Escape to close the program            " << std::endl
              << "=====================================================" << std::endl;

    // Starts the app main loop
    update();

	for (int i = 0; i < objects.size(); i++) {
		delete objects[i];
	}

    // Stops the glfw program
    glfwTerminate();

    return 0;
}

void mouse_callback(GLFWwindow* window, double xpos, double ypos) {

	if (pressLeft) {
		camera->mouseUpdate(glm::vec2(xpos, ypos));
	}

	TwMouseMotion(static_cast<int>(xpos), static_cast<int>(ypos));
}

void onMouseButton(GLFWwindow* window, int button, int action, int mods)
{
	auto a = action == GLFW_PRESS ? TW_MOUSE_PRESSED : TW_MOUSE_RELEASED;
	auto b = TW_MOUSE_LEFT;

	pressMenu = TwMouseButton(a, b);
	//std::cout << "hola" << std::endl;

	if (action == GLFW_PRESS && !pressMenu) {

		pressLeft = true;

	}
	else {
		pressLeft = false;
	}

}
