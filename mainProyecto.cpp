/*---------------------------------------------------------------------*/
/* ---------------------  Proyecto Final -----------------------------*/
/*--------- Computación Gráfico e Interacción Humano-Computadora------*/
/*-----------------------    2021-1   ---------------------------*/
/*------------- Alumno: Gómez Domínguez Norma Sthepanie---------------*/
/*----------------------------------------------------------------*/

#include <Windows.h>

#include <glad/glad.h>
#include <glfw3.h>	//main
#include <stdlib.h>		
#include <glm/glm.hpp>	//camera y model
#include <glm/gtc/matrix_transform.hpp>	//camera y model
#include <glm/gtc/type_ptr.hpp>
#include<time.h>


#define STB_IMAGE_IMPLEMENTATION
#include <stb_image.h>	//Texture

#define SDL_MAIN_HANDLED
#include <SDL/SDL.h>

#include <shader_m.h>
#include <camera.h>
#include <modelAnim.h>
#include <model.h>
#include <Skybox.h>
#include <iostream>

#include<irrKlang.h>

//#pragma comment(lib, "winmm.lib")

void framebuffer_size_callback(GLFWwindow* window, int width, int height);
void mouse_callback(GLFWwindow* window, double xpos, double ypos);
void scroll_callback(GLFWwindow* window, double xoffset, double yoffset);
//void my_input(GLFWwindow *window);
void my_input(GLFWwindow* window, int key, int scancode, int action, int mods);
void animate(void);

// settings
const unsigned int SCR_WIDTH = 800;
const unsigned int SCR_HEIGHT = 600;

// camera
float xIni = -60.0f;
float yIni = 10.0f;
float zIni = 580.0f;
float xAvance = 0.0f;
float yAvance = 0.0f;
float zAvance = 0.0f;
bool reco1 = false;
bool reco2 = false;
bool reco3 = false;
bool reco4 = false;
Camera camera(glm::vec3(10.0f, 20.0f, 180.0f));
float MovementSpeed = 0.1f;
float lastX = SCR_WIDTH / 2.0f;
float lastY = SCR_HEIGHT / 2.0f;
bool firstMouse = true;

int tiempo = 0;

//variables tablon con skate
float skateY = 0.0f;
float skateZ = 0.0f;
float skaterotY = 0.0f;
float skateRotZ = 0.0f;
float rotTablonY = 0.0f;
bool ida = true;

//variables coche
bool permisoIda = true;
bool cocheIda = false;
bool permisoRegreso = false;
bool cocheRegreso = false;
float cocheX = 0.0f;
float cocheZ = 0.0f;
float rotCocheY = 0.0f;

//variables columpio
float rotSwingY;
bool vuelta = true;

//variables animacion tele
float tiempoTele = 0.0f;
bool animTele = false;
bool musicTele = false;

float rotPhone = 0.0f;
bool ringPhone = true;
bool ringIda = false;
bool ringRegreso = false;

bool musicFondo = true;

using namespace irrklang;


bool reco = false;


// timing
const int FPS = 60;
const int LOOP_TIME = 1000 / FPS; // = 16 milisec // 1000 millisec == 1 sec
double	deltaTime = 0.0f,
lastFrame = 0.0f;

//Lighting
glm::vec3 lightPosition(0.0f, 4.0f, -10.0f);
glm::vec3 lightDirection(0.0f, -1.0f, -1.0f);

// posiciones
//float x = 0.0f;
//float y = 0.0f;
float	movAuto_x = 0.0f,
movAuto_z = 0.0f,
orienta = 0.0f;
bool	animacion = false,
recorrido1 = true,
recorrido2 = false,
recorrido3 = false,
recorrido4 = false;


//Keyframes (Manipulación y dibujo)
float	posX = 0.0f,
posY = 0.0f,
posZ = 0.0f,
rotRodIzq = 0.0f,
giroMonito = 0.0f;
//gatito
float movCola = 0.0f,
rotpataizq = 0.0f,
rotpatader = 0.0f,
rotparizqtra = 0.0f,
rotpardertra = 0.0f,
movCabeza = 0.0f,
movTorso = 0.0f;

float	incX = 0.0f,
incY = 0.0f,
incZ = 0.0f,
rotInc = 0.0f,
giroMonitoInc = 0.0f,
movColainc = 0.0f,
rotpataizqinc = 0.0f,
rotpataderinc = 0.0f,
rotparizqtrainc = 0.0f,
rotpardertrainc = 0.0f,
movCabezainc = 0.0f,
movTorsoinc = 0.0f;

//Kid

float	kidposX = 0.0f,
kidposY = 0.0f,
kidposZ = 0.0f,
movCabezaKid = 0.0f,
movcuerpo = 0.0f,
movpieIzq = 0.0f,
movpieDer = 0.0f,
movbrazoIzq = 0.0f,
movbrazoDer = 0.0f,
movBalon = 0.0f;

float	kidposXinc = 0.0f,
kidposYinc = 0.0f,
kidposZinc = 0.0f,
movCabezaKidinc = 0.0f,
movcuerpoinc = 0.0f,
movpieIzqinc = 0.0f,
movpieDerinc = 0.0f,
movbrazoIzqinc = 0.0f,
movbrazoDerinc = 0.0f,
movBaloninc = 0.0f;

#define MAX_FRAMES 50
int i_max_steps = 60;
int i_curr_steps = 0;
typedef struct _frame
{
	//Variables para GUARDAR Key Frames
	float posX;		//Variable para PosicionX
	float posY;		//Variable para PosicionY
	float posZ;		//Variable para PosicionZ
	float rotRodIzq;
	float giroMonito;
	float movCola = 0.0f;
	float rotpataizq = 0.0f;
	float rotpatader = 0.0f;
	float rotparizqtra = 0.0f;
	float rotpardertra = 0.0f;
	float movCabeza = 0.0f;
	float movTorso = 0.0f;
	float kidposX = 0.0f;
	float kidposY = 0.0f;
	float kidposZ = 0.0f;
	float movCabezaKid = 0.0f;
	float movcuerpo = 0.0f;
	float movpieIzq = 0.0f;
	float movpieDer = 0.0f;
	float movbrazoIzq = 0.0f;
	float movbrazoDer = 0.0f;
	float movBalon = 0.0f;

}FRAME;

FRAME KeyFrame[MAX_FRAMES];
int FrameIndex = 5;			//introducir datos
bool play = false;
int playIndex = 0;

void saveFrame(void)
{
	//printf("frameindex %d\n", FrameIndex);
	std::cout << "Frame Index = " << FrameIndex << std::endl;

	KeyFrame[FrameIndex].posX = posX;
	KeyFrame[FrameIndex].posY = posY;
	KeyFrame[FrameIndex].posZ = posZ;

	KeyFrame[FrameIndex].rotRodIzq = rotRodIzq;
	KeyFrame[FrameIndex].giroMonito = giroMonito;

	//gatito
	KeyFrame[FrameIndex].posX = posX;
	KeyFrame[FrameIndex].posY = posY;
	KeyFrame[FrameIndex].posZ = posZ;

	KeyFrame[FrameIndex].movCola = movCola;
	KeyFrame[FrameIndex].rotpataizq = rotpataizq;
	KeyFrame[FrameIndex].rotpatader = rotpatader;

	KeyFrame[FrameIndex].rotparizqtra = rotparizqtra;

	KeyFrame[FrameIndex].rotpardertra = rotpardertra;
	KeyFrame[FrameIndex].movCabeza = movCabeza;

	KeyFrame[FrameIndex].movTorso = movTorso;

	//kid

	KeyFrame[FrameIndex].kidposX = kidposX;
	KeyFrame[FrameIndex].kidposY = kidposY;
	KeyFrame[FrameIndex].kidposZ = kidposZ;
	KeyFrame[FrameIndex].movCabezaKid = movCabezaKid;
	KeyFrame[FrameIndex].movpieIzq = movpieIzq;
	KeyFrame[FrameIndex].movpieDer = movpieDer;

	KeyFrame[FrameIndex].movcuerpo = movcuerpo;

	KeyFrame[FrameIndex].movbrazoIzq = movbrazoIzq;
	KeyFrame[FrameIndex].movbrazoDer = movbrazoDer;


	KeyFrame[FrameIndex].movBalon = movBalon;

	FrameIndex++;
}

void resetElements(void)
{
	posX = KeyFrame[0].posX;
	posY = KeyFrame[0].posY;
	posZ = KeyFrame[0].posZ;

	rotRodIzq = KeyFrame[0].rotRodIzq;
	giroMonito = KeyFrame[0].giroMonito;
	//Gatito
	movCola = KeyFrame[0].movCola;
	rotpataizq = KeyFrame[0].rotpataizq;

	rotpatader = KeyFrame[0].rotpatader;
	rotparizqtra = KeyFrame[0].rotparizqtra;
	rotpardertra = KeyFrame[0].rotpardertra;
	movCabeza = KeyFrame[0].movCabeza;
	movTorso = KeyFrame[0].movTorso;

	//kid

	kidposX = KeyFrame[0].kidposX;
	kidposY = KeyFrame[0].kidposY;
	kidposZ = KeyFrame[0].kidposZ;
	movCabezaKid = KeyFrame[0].movCabezaKid;
	movpieIzq = KeyFrame[0].movpieIzq;

	movpieDer = KeyFrame[0].movpieDer;
	movcuerpo = KeyFrame[0].movcuerpo;
	movbrazoIzq = KeyFrame[0].movbrazoIzq;
	movbrazoDer = KeyFrame[0].movbrazoDer;
	movBalon = KeyFrame[0].movBalon;
}

void interpolation(void)
{
	incX = (KeyFrame[playIndex + 1].posX - KeyFrame[playIndex].posX) / i_max_steps;
	incY = (KeyFrame[playIndex + 1].posY - KeyFrame[playIndex].posY) / i_max_steps;
	incZ = (KeyFrame[playIndex + 1].posZ - KeyFrame[playIndex].posZ) / i_max_steps;

	rotInc = (KeyFrame[playIndex + 1].rotRodIzq - KeyFrame[playIndex].rotRodIzq) / i_max_steps;
	giroMonitoInc = (KeyFrame[playIndex + 1].giroMonito - KeyFrame[playIndex].giroMonito) / i_max_steps;

	//Gatito
	incX = (KeyFrame[playIndex + 1].posX - KeyFrame[playIndex].posX) / i_max_steps;
	incY = (KeyFrame[playIndex + 1].posY - KeyFrame[playIndex].posY) / i_max_steps;
	incZ = (KeyFrame[playIndex + 1].posZ - KeyFrame[playIndex].posZ) / i_max_steps;

	movColainc = (KeyFrame[playIndex + 1].movCola - KeyFrame[playIndex].movCola) / i_max_steps;
	rotpataizqinc = (KeyFrame[playIndex + 1].rotpataizq - KeyFrame[playIndex].rotpataizq) / i_max_steps;
	rotpataderinc = (KeyFrame[playIndex + 1].rotpatader - KeyFrame[playIndex].rotpatader) / i_max_steps;
	rotparizqtrainc = (KeyFrame[playIndex + 1].rotparizqtra - KeyFrame[playIndex].rotparizqtra) / i_max_steps;
	rotpardertrainc = (KeyFrame[playIndex + 1].rotpardertra - KeyFrame[playIndex].rotpardertra) / i_max_steps;
	movCabezainc = (KeyFrame[playIndex + 1].movCabeza - KeyFrame[playIndex].movCabeza) / i_max_steps;
	movTorsoinc = (KeyFrame[playIndex + 1].movTorso - KeyFrame[playIndex].movTorso) / i_max_steps;

	//Kid

	kidposXinc = (KeyFrame[playIndex + 1].kidposX - KeyFrame[playIndex].kidposX) / i_max_steps;
	kidposYinc = (KeyFrame[playIndex + 1].kidposY - KeyFrame[playIndex].kidposY) / i_max_steps;
	kidposZinc = (KeyFrame[playIndex + 1].kidposZ - KeyFrame[playIndex].kidposZ) / i_max_steps;
	movCabezaKidinc = (KeyFrame[playIndex + 1].movCabezaKid - KeyFrame[playIndex].movCabezaKid) / i_max_steps;
	movpieIzqinc = (KeyFrame[playIndex + 1].movpieIzq - KeyFrame[playIndex].movpieIzq) / i_max_steps;
	movpieDerinc = (KeyFrame[playIndex + 1].movpieDer - KeyFrame[playIndex].movpieDer) / i_max_steps;
	movcuerpoinc = (KeyFrame[playIndex + 1].movcuerpo - KeyFrame[playIndex].movcuerpo) / i_max_steps;
	movbrazoIzqinc = (KeyFrame[playIndex + 1].movbrazoIzq - KeyFrame[playIndex].movbrazoIzq) / i_max_steps;
	movbrazoDerinc = (KeyFrame[playIndex + 1].movbrazoDer - KeyFrame[playIndex].movbrazoDer) / i_max_steps;
	movBaloninc = (KeyFrame[playIndex + 1].movBalon - KeyFrame[playIndex].movBalon) / i_max_steps;
}


void animate(void)
{
	if (play)
	{
		if (i_curr_steps >= i_max_steps) //end of animation between frames?
		{
			playIndex++;
			if (playIndex > FrameIndex - 2)	//end of total animation?
			{
				std::cout << "Animation ended" << std::endl;
				//printf("termina anim\n");
				playIndex = 0;
				play = false;
			}
			else //Next frame interpolations
			{
				i_curr_steps = 0; //Reset counter
								  //Interpolation
				interpolation();
			}
		}
		else
		{
			//Draw animation
			posX += incX;
			posY += incY;
			posZ += incZ;

			rotRodIzq += rotInc;
			giroMonito += giroMonitoInc;

			//Gatito
			movCola += movColainc;
			rotpataizq += rotpataizqinc;
			rotpatader += rotpataderinc;
			rotparizqtra += rotparizqtrainc;
			rotpardertra += rotpardertrainc;
			movCabeza += movCabezainc;
			movTorso += movTorsoinc;

			//kid
			movCabezaKid += movCabezainc;
			movpieIzq += movpieIzqinc;
			movpieDer += movpieDerinc;
			movbrazoIzq += movbrazoIzqinc;
			movbrazoDer += movbrazoDerinc;
			movcuerpo += movcuerpoinc;
			movBalon += movBaloninc;
			kidposX += kidposXinc;
			kidposY += kidposYinc;
			kidposZ += kidposZinc;

			i_curr_steps++;
		}
	}

	//Vehículo
	if (animacion)
	{
		if (recorrido1)
		{
			movAuto_z += 3.7f;
			orienta = 0.0f;
			if (movAuto_z > 150.0f)
			{
				recorrido1 = false;
				recorrido2 = true;
			}
		}
		if (recorrido2)
		{
			movAuto_x -= 3.0f;
			orienta = -90.0f;
			if (movAuto_x < -200.0f)
			{
				recorrido2 = false;
				recorrido3 = true;
			}
		}
		if (recorrido3)
		{
			movAuto_z -= 3.0f;
			orienta = 180.0f;
			if (movAuto_z < -150.0f)
			{
				recorrido3 = false;
				recorrido4 = true;
			}
		}
		if (recorrido4)
		{
			movAuto_x += 2.7f;
			orienta = 90.0f;
			if (movAuto_x > 0.0f)
			{
				recorrido4 = false;
				recorrido1 = true;
			}
		}
	}
}

int main()
{
	// glfw: initialize and configure
	// ------------------------------
	glfwInit();
	/*glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);*/

#ifdef __APPLE__
	glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);
#endif

	// glfw window creation
	// --------------------
	GLFWwindow* window = glfwCreateWindow(SCR_WIDTH, SCR_HEIGHT, "Proyecto Final Gomez Dominguez Norma Sthepanie", NULL, NULL);
	if (window == NULL)
	{
		std::cout << "Failed to create GLFW window" << std::endl;
		glfwTerminate();
		return -1;
	}
	glfwMakeContextCurrent(window);
	glfwSetFramebufferSizeCallback(window, framebuffer_size_callback);
	glfwSetCursorPosCallback(window, mouse_callback);
	glfwSetScrollCallback(window, scroll_callback);
	glfwSetKeyCallback(window, my_input);

	// tell GLFW to capture our mouse
	glfwSetInputMode(window, GLFW_CURSOR, GLFW_CURSOR_DISABLED);

	// glad: load all OpenGL function pointers
	// ---------------------------------------
	if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress))
	{
		std::cout << "Failed to initialize GLAD" << std::endl;
		return -1;
	}

	// configure global opengl state
	// -----------------------------
	glEnable(GL_DEPTH_TEST);

	// build and compile shaders
	// -------------------------
	//Shader staticShader("Shaders/lightVertex.vs", "Shaders/lightFragment.fs");
	Shader staticShader("Shaders/shader_Lights.vs", "Shaders/shader_Lights.fs");
	Shader skyboxShader("Shaders/skybox.vs", "Shaders/skybox.fs");
	Shader animShader("Shaders/anim.vs", "Shaders/anim.fs");

	vector<std::string> faces, nightFaces;

	faces.push_back("resources/skybox/right.jpg");
	faces.push_back("resources/skybox/left.jpg");
	faces.push_back("resources/skybox/top.jpg");
	faces.push_back("resources/skybox/bottom.jpg");
	faces.push_back("resources/skybox/front.jpg");
	faces.push_back("resources/skybox/back.jpg");

	nightFaces.push_back("resources/skybox/right2.jpg");
	nightFaces.push_back("resources/skybox/left2.jpg");
	nightFaces.push_back("resources/skybox/top2.jpg");
	nightFaces.push_back("resources/skybox/bottom.jpg");
	nightFaces.push_back("resources/skybox/front2.jpg");
	nightFaces.push_back("resources/skybox/back2.jpg");


	/*vector<std::string> nightFaces{
		"resources/skybox/right2.jpg",
		"resources/skybox/left2.jpg",
		"resources/skybox/top2.jpg",
		"resources/skybox/bottom.jpg",
		"resources/skybox/front2.jpg",
		"resources/skybox/back2.jpg"
	};*/

	Skybox skybox = Skybox(faces);
	skyboxShader.setInt("skybox", 0);
	Skybox skybox2 = Skybox(nightFaces);
	skyboxShader.setInt("skybox2", 1);
	// Shader configuration
	// --------------------
	skyboxShader.use();
	//skyboxShader.setInt("skybox", 0);


	// load models
	// -----------
	Model piso("resources/objects/piso/piso.obj");
	/*Model botaDer("resources/objects/Personaje/bota.obj");
	Model piernaDer("resources/objects/Personaje/piernader.obj");
	Model piernaIzq("resources/objects/Personaje/piernader.obj");
	Model torso("resources/objects/Personaje/torso.obj");
	Model brazoDer("resources/objects/Personaje/brazoder.obj");
	Model brazoIzq("resources/objects/Personaje/brazoizq.obj");
	Model cabeza("resources/objects/Personaje/cabeza.obj");
	Model carro("resources/objects/lambo/carroceria.obj");
	Model llanta("resources/objects/lambo/Wheel.obj");
	Model cubo("resources/objects/Cubo/cube01.obj"); */
	Model vecindario("resources/objects/Vecindario/Vecindario/vecindario.fbx");
	Model casaDoll("resources/objects/casa/DollHouse.obj");
	Model casaVieja("resources/objects/casa/OldHouse.obj");
	Model casita("resources/objects/casa/casa/casa.fbx");
	Model oBed("resources/objects/OBed/ObjBed.fbx");
	Model table("resources/objects/table/round_table.obj");
	Model smallTable("resources/objects/SmallTable/Dr_furnit_Smallbasis.obj");
	Model basicTable("resources/objects/BasicTable/otukue2.obj");
	Model patioTable("resources/objects/TableOutside/tableoutside.obj");
	Model livinTable("resources/objects/table/o_table_prl.obj");
	Model smallSofa("resources/objects/WhiteSofa/White Sofa.obj");
	Model sofa("resources/objects/ZebraPrintSofa/Zebra Print Sofa.obj");
	Model alfSofa("resources/objects/RattanSofa/Rattan Sofa.obj");
	Model toilet("resources/objects/ToiletCheap/ToiletCheap.obj");
	Model sink("resources/objects/Sink/sink.obj");
	Model washing("resources/objects/WashingMachine/laundry_machine.obj");
	Model bathtub("resources/objects/Bathtub/Bathtube.obj");
	Model tv("resources/objects/TV/TV.fbx");
	Model estufa("resources/objects/Cookingstove/cookingstove_clean.obj");
	Model tarja("resources/objects/LabSink/Lab Sink.obj");
	Model barra("resources/objects/Barcorner/EDU_Restaurant_barcounterStraight256.obj");
	Model coche("resources/objects/homer_v/homer_v.obj");
	Model rasho("resources/objects/Mcqueen/Lightning2.obj");
	Model skate("resources/objects/RollerSkate/rollerskate.obj");
	Model tablon("resources/objects/Jonny/tablon.obj");
	Model pool("resources/objects/pool/pool.fbx");
	Model ramp("resources/objects/Ramp/ramp.obj");
	Model tree("resources/objects/Tree/savannahTreetigg.obj");
	Model swing("resources/objects/swing/swing.fbx");
	Model telephoneBase("resources/objects/Phone/base.obj");
	Model telephone("resources/objects/Phone/telephone.obj");


	//modelo kid
	Model kidBody("resources/objects/Jonny/body.obj");
	Model kidHead("resources/objects/Jonny/head.obj");
	Model kidR_arm("resources/objects/Jonny/r_arm.obj");
	Model kidL_arm("resources/objects/Jonny/l_arm.obj");
	Model kidR_leg("resources/objects/Jonny/r_leg.obj");
	Model kidL_leg("resources/objects/Jonny/l_leg.obj");
	Model kidBall("resources/objects/SoccerBall/Soccer Ball.obj");

	//Modelo gato
	Model catBody("resources/objects/StandardCat/body.obj");
	Model catHead("resources/objects/StandardCat/head.obj");
	Model catR_arm("resources/objects/StandardCat/r_arm.obj");
	Model catL_arm("resources/objects/StandardCat/l_arm.obj");
	Model catR_leg("resources/objects/StandardCat/r_leg.obj");
	Model catL_leg("resources/objects/StandardCat/l_leg.obj");
	Model catTail("resources/objects/StandardCat/tail.obj");

	//tele animacion
	Model tele1("resources/objects/burger/burguer1.fbx");
	Model tele2("resources/objects/burger/burguer2.fbx");
	Model tele3("resources/objects/burger/burguer3.fbx");
	Model tele4("resources/objects/burger/burguer4.fbx");

	//cerca
	Model cerca("resources/objects/65-fence/fence.fbx");

	//bancos
	Model bench("resources/objects/bench/bench.fbx");
	Model columpio("resources/objects/woodswing/Models and Textures/woodswing.fbx");



	/*ModelAnim animacionPersonaje("resources/objects/Personaje1/PersonajeBrazo.dae");
	animacionPersonaje.initShaders(animShader.ID);

	ModelAnim ninja("resources/objects/ZombieWalk/ZombieWalk.dae");
	ninja.initShaders(animShader.ID);*/

	//musica
	ISoundEngine* engine = createIrrKlangDevice();
	ISoundEngine* engine2 = createIrrKlangDevice();

	if (!engine)
		return 0;

	ISound* ambiental = engine->play2D("Audio/All Star - Smash Mouth [Lyrics].mp3", true);
	ISound* ambiental2 = engine2->play2D("Audio/cheeseburger-family-jack-stauber.mp3", true);



	//Inicialización de KeyFrames
	/*for (int i = 0; i < MAX_FRAMES; i++)
	{
		KeyFrame[i].posX = 0;
		KeyFrame[i].posY = 0;
		KeyFrame[i].posZ = 0;
		KeyFrame[i].rotRodIzq = 0;
		KeyFrame[i].giroMonito = 0;
	}*/

	// draw in wireframe
	{
		KeyFrame[0].posX = 0;
		KeyFrame[0].posY = 0;
		KeyFrame[0].posZ = 0;
		KeyFrame[0].movCola = 0;
		KeyFrame[0].rotpataizq = 0;
		KeyFrame[0].rotpatader = 0;
		KeyFrame[0].rotparizqtra = 0;
		KeyFrame[0].rotpardertra = 0;
		KeyFrame[0].movCabeza = 0;
		KeyFrame[0].movTorso = 0;

		KeyFrame[1].posX = 2.0f;
		KeyFrame[1].posY = 0;
		KeyFrame[1].posZ = 0;
		KeyFrame[1].movCola = 90.0f;
		KeyFrame[1].rotpataizq = 45.0f;
		KeyFrame[1].rotpatader = -45.0f;
		KeyFrame[1].rotparizqtra = 45.0f;
		KeyFrame[1].rotpardertra = -45.0f;
		KeyFrame[1].movCabeza = 45.0f;
		KeyFrame[1].movTorso = 0;

		KeyFrame[2].posX = -5.0f;
		KeyFrame[2].posY = 0;
		KeyFrame[2].posZ = 0;
		KeyFrame[2].movCola = -45.0f;
		KeyFrame[2].rotpataizq = -45.0f;
		KeyFrame[2].rotpatader = 45.0f;
		KeyFrame[2].rotparizqtra = -45.0f;
		KeyFrame[2].rotpardertra = 45.0f;
		KeyFrame[2].movCabeza = -45.0f;
		KeyFrame[2].movTorso = 90.0f;

		KeyFrame[3].posX = 5.0f;
		KeyFrame[3].posY = 10.0f;
		KeyFrame[3].posZ = 3.0f;
		KeyFrame[3].movCola = 45.0f;
		KeyFrame[3].rotpataizq = 0;
		KeyFrame[3].rotpatader = 0;
		KeyFrame[3].rotparizqtra = -45.0f;
		KeyFrame[3].rotpardertra = 45.0f;
		KeyFrame[3].movCabeza = 45.0f;
		KeyFrame[3].movTorso = -180.0f;

		KeyFrame[4].posX = 0;
		KeyFrame[4].posY = 0;
		KeyFrame[4].posZ = -3.0f;
		KeyFrame[4].movCola = -45.0f;
		KeyFrame[4].rotpataizq = 0;
		KeyFrame[4].rotpatader = 0;
		KeyFrame[4].rotparizqtra = 45.0;
		KeyFrame[4].rotpardertra = -45.0;
		KeyFrame[4].movCabeza = -45.0f;
		KeyFrame[4].movTorso = 180.0f;

		//KID
		KeyFrame[0].kidposX = 10.0f;
		KeyFrame[0].kidposY = 0;
		KeyFrame[0].kidposZ = 0;
		KeyFrame[0].movCabezaKid = 0;
		KeyFrame[0].movpieIzq = 0;
		KeyFrame[0].movpieDer = 0;
		KeyFrame[0].movcuerpo = 0;
		KeyFrame[0].movbrazoIzq = 0;
		KeyFrame[0].movbrazoDer = 0;
		KeyFrame[0].movBalon = 0;

		KeyFrame[1].kidposX = 10.0f;
		KeyFrame[1].kidposY = 0.0f;
		KeyFrame[1].kidposZ = 10.0f;
		KeyFrame[1].movCabezaKid = 45.0f;
		KeyFrame[1].movpieIzq = -45.0f;
		KeyFrame[1].movpieDer = 45.0f;
		KeyFrame[1].movcuerpo = -45.0f;
		KeyFrame[1].movbrazoIzq = 45.0f;
		KeyFrame[1].movbrazoDer = -45.0f;
		KeyFrame[1].movBalon = 0;

		KeyFrame[2].kidposX = -20.0f;
		KeyFrame[2].kidposY = 0.0f;
		KeyFrame[2].kidposZ = -10.0f;
		KeyFrame[2].movCabezaKid = -45.0f;
		KeyFrame[2].movpieIzq = 45.0f;
		KeyFrame[2].movpieDer = -45.0f;
		KeyFrame[2].movcuerpo = 45.0f;
		KeyFrame[2].movbrazoIzq = -45.0f;
		KeyFrame[2].movbrazoDer = 45.0f;
		KeyFrame[2].movBalon = 10;

		KeyFrame[3].kidposX = 0.0f;
		KeyFrame[3].kidposY = 0.0f;
		KeyFrame[3].kidposZ = 0.0f;
		KeyFrame[3].movCabezaKid = 0;
		KeyFrame[3].movpieIzq = 0;
		KeyFrame[3].movpieDer = 0;
		KeyFrame[3].movcuerpo = 0;
		KeyFrame[3].movbrazoIzq = 0;
		KeyFrame[3].movbrazoDer = 0;
		KeyFrame[3].movBalon = -10;
	}

	//glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);

	// render loop
	// -----------
	while (!glfwWindowShouldClose(window))
	{
		skyboxShader.setInt("skybox", 0);

		// per-frame time logic
		// --------------------
		lastFrame = SDL_GetTicks();

		// input
		// -----
		//my_input(window);
		animate();

		// render
		// ------
		glClearColor(0.3f, 0.3f, 0.3f, 1.0f);
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

		// don't forget to enable shader before setting uniforms
		staticShader.use();
		//Setup Advanced Lights
		staticShader.setVec3("viewPos", camera.Position);
		staticShader.setVec3("dirLight.direction", lightDirection);
		staticShader.setVec3("dirLight.ambient", glm::vec3(0.2f, 0.2f, 0.2f));
		staticShader.setVec3("dirLight.diffuse", glm::vec3(1.0f - tiempo, 1.0f - tiempo, 1.0f - tiempo));
		staticShader.setVec3("dirLight.specular", glm::vec3(0.0f, 0.0f, 0.0f));

		staticShader.setVec3("pointLight[0].position", lightPosition);
		staticShader.setVec3("pointLight[0].ambient", glm::vec3(0.0f, 0.0f, 0.0f));
		staticShader.setVec3("pointLight[0].diffuse", glm::vec3(0.0f, 0.0f, 0.0f));
		staticShader.setVec3("pointLight[0].specular", glm::vec3(0.0f, 0.0f, 0.0f));
		staticShader.setFloat("pointLight[0].constant", 0.8f);
		staticShader.setFloat("pointLight[0].linear", 0.009f);
		staticShader.setFloat("pointLight[0].quadratic", 0.032f);

		staticShader.setVec3("pointLight[1].position", glm::vec3(0.0, 0.0f, 0.0f));
		staticShader.setVec3("pointLight[1].ambient", glm::vec3(0.0f, 0.0f, 0.0f));
		staticShader.setVec3("pointLight[1].diffuse", glm::vec3(0.0f, 0.0f, 0.0f));
		staticShader.setVec3("pointLight[1].specular", glm::vec3(0.0f, 0.0f, 0.0f));
		staticShader.setFloat("pointLight[1].constant", 1.0f);
		staticShader.setFloat("pointLight[1].linear", 0.009f);
		staticShader.setFloat("pointLight[1].quadratic", 0.032f);

		staticShader.setFloat("material_shininess", 32.0f);

		glm::mat4 model = glm::mat4(1.0f);
		glm::mat4 tmp = glm::mat4(1.0f);
		// view/projection transformations
		glm::mat4 projection = glm::perspective(glm::radians(camera.Zoom), (float)SCR_WIDTH / (float)SCR_HEIGHT, 0.1f, 10000.0f);
		glm::mat4 view = camera.GetViewMatrix();
		staticShader.setMat4("projection", projection);
		staticShader.setMat4("view", view);

		//// Light
		glm::vec3 lightColor = glm::vec3(1.0f);
		glm::vec3 diffuseColor = lightColor * glm::vec3(0.5f);
		glm::vec3 ambientColor = diffuseColor * glm::vec3(0.75f);




		// -------------------------------------------------------------------------------------------------------------------------
		// Personaje Animacion
		// -------------------------------------------------------------------------------------------------------------------------
		//Remember to activate the shader with the animation
		animShader.use();
		animShader.setMat4("projection", projection);
		animShader.setMat4("view", view);

		animShader.setVec3("material.specular", glm::vec3(0.5f));
		animShader.setFloat("material.shininess", 32.0f);
		animShader.setVec3("light.ambient", ambientColor);
		animShader.setVec3("light.diffuse", diffuseColor);
		animShader.setVec3("light.specular", 1.0f, 1.0f, 1.0f);
		animShader.setVec3("light.direction", lightDirection);
		animShader.setVec3("viewPos", camera.Position);

		//model = glm::translate(glm::mat4(1.0f), glm::vec3(-40.3f, 1.75f, 0.3f)); // translate it down so it's at the center of the scene
		//model = glm::scale(model, glm::vec3(1.2f));	// it's a bit too big for our scene, so scale it down
		//model = glm::rotate(model, glm::radians(90.0f), glm::vec3(0.0f, 1.0f, 0.0f));
		//animShader.setMat4("model", model);
		//animacionPersonaje.Draw(animShader);

		// -------------------------------------------------------------------------------------------------------------------------
		// Segundo Personaje Animacion
		// -------------------------------------------------------------------------------------------------------------------------

		//model = glm::translate(glm::mat4(1.0f), glm::vec3(40.3f, 1.75f, 0.3f)); // translate it down so it's at the center of the scene
		//model = glm::scale(model, glm::vec3(0.5f));	// it's a bit too big for our scene, so scale it down
		//model = glm::rotate(model, glm::radians(90.0f), glm::vec3(0.0f, 1.0f, 0.0f));
		//animShader.setMat4("model", model);
		//ninja.Draw(animShader);

		// -------------------------------------------------------------------------------------------------------------------------
		// Escenario
		// -------------------------------------------------------------------------------------------------------------------------
		staticShader.use();
		staticShader.setMat4("projection", projection);
		staticShader.setMat4("view", view);

		//Plano del piso
		model = glm::mat4(1.0f);
		model = glm::translate(model, glm::vec3(0.0f, -1.0f, 0.0f));
		model = glm::scale(model, glm::vec3(0.2f));
		staticShader.setMat4("model", model);
		piso.Draw(staticShader);

		//vecindario
		model = glm::rotate(glm::mat4(1.0f), glm::radians(-90.0f), glm::vec3(1.0f, 0.0f, 0.0f));
		model = glm::translate(model, glm::vec3(5.0f, -180.0f, -24.45f));
		model = glm::scale(model, glm::vec3(0.001f, 0.001f, 0.001f));
		staticShader.setMat4("model", model);
		vecindario.Draw(staticShader);

		//casa 1 casa principal
		model = glm::rotate(glm::mat4(1.0f), glm::radians(-90.0f), glm::vec3(1.0f, 0.0f, 0.0f));
		model = glm::translate(model, glm::vec3(5.0f, 95.0f, 25.0f));
		model = glm::scale(model, glm::vec3(2.5f, 2.5f, 2.5f));
		staticShader.setMat4("model", model);
		casita.Draw(staticShader);

		//Casa 2
		model = glm::translate(glm::mat4(1.0f), glm::vec3(150.0f, 0.0f, 310.0f));
		model = glm::scale(model, glm::vec3(1.5f, 1.5f, 1.5f));
		model = glm::rotate(model, glm::radians(-90.0f), glm::vec3(0.0f, 1.0f, 0.0f));
		staticShader.setMat4("model", model);
		casaDoll.Draw(staticShader);

		//casa 3
		model = glm::translate(glm::mat4(1.0f), glm::vec3(-150.0f, 0.0f, 310.0f));
		model = glm::scale(model, glm::vec3(1.5f, 1.5f, 1.5f));
		model = glm::rotate(model, glm::radians(90.0f), glm::vec3(0.0f, 1.0f, 0.0f));
		staticShader.setMat4("model", model);
		casaDoll.Draw(staticShader);

		//casa 4
		model = glm::translate(glm::mat4(1.0f), glm::vec3(120.0f, 0.0f, 470.0f));
		model = glm::scale(model, glm::vec3(6.0f));
		model = glm::rotate(model, glm::radians(-90.0f), glm::vec3(0.0f, 1.0f, 0.0f));
		staticShader.setMat4("model", model);
		casaVieja.Draw(staticShader);

		//casa 5
		model = glm::translate(glm::mat4(1.0f), glm::vec3(-120.0f, 0.0f, 470.0f));
		model = glm::scale(model, glm::vec3(6.0f));
		model = glm::rotate(model, glm::radians(90.0f), glm::vec3(0.0f, 1.0f, 0.0f));
		staticShader.setMat4("model", model);
		casaVieja.Draw(staticShader);



		//camas
		//Cama Bedroom1
		model = glm::rotate(glm::mat4(1.0f), glm::radians(-90.0f), glm::vec3(1.0f, 0.0f, 0.0f));
		model = glm::translate(model, glm::vec3(-25.0f, -21.0f, 0.0f));
		model = glm::scale(model, glm::vec3(7.0f, 7.0f, 7.0f));
		model = glm::rotate(model, glm::radians(90.0f), glm::vec3(0.0f, 0.0f, 1.0));
		staticShader.setMat4("model", model);
		oBed.Draw(staticShader);
		//cama Bedroom2
		model = glm::rotate(glm::mat4(1.0f), glm::radians(-90.0f), glm::vec3(1.0f, 0.0f, 0.0f));
		model = glm::translate(model, glm::vec3(-15.0f, 19.0f, 0.0f));
		model = glm::scale(model, glm::vec3(5.0f, 5.0f, 5.0f));
		model = glm::rotate(model, glm::radians(180.0f), glm::vec3(0.0f, 0.0f, 1.0));
		staticShader.setMat4("model", model);
		oBed.Draw(staticShader);
		//cama Bedroom 3-1
		model = glm::rotate(glm::mat4(1.0f), glm::radians(-90.0f), glm::vec3(1.0f, 0.0f, 0.0f));
		model = glm::translate(model, glm::vec3(-10.0f, 140.0f, 0.0f));
		model = glm::scale(model, glm::vec3(5.0f, 5.0f, 5.0f));
		staticShader.setMat4("model", model);
		oBed.Draw(staticShader);
		//cama Bedroom 3-2
		model = glm::rotate(glm::mat4(1.0f), glm::radians(-90.0f), glm::vec3(1.0f, 0.0f, 0.0f));
		model = glm::translate(model, glm::vec3(-25.0f, 140.0f, 0.0f));
		model = glm::scale(model, glm::vec3(5.0f, 5.0f, 5.0f));
		staticShader.setMat4("model", model);
		oBed.Draw(staticShader);

		//mesas
		//mesa bedromm1-1
		model = glm::rotate(glm::mat4(1.0f), glm::radians(0.0f), glm::vec3(1.0f, 0.0f, 0.0f));
		model = glm::translate(model, glm::vec3(-29.0f, 0.0f, 31.0f));
		model = glm::scale(model, glm::vec3(8.0f, 8.0f, 8.0f));
		staticShader.setMat4("model", model);
		table.Draw(staticShader);
		//mesa bedromm1-2
		model = glm::rotate(glm::mat4(1.0f), glm::radians(0.0f), glm::vec3(1.0f, 0.0f, 0.0f));
		model = glm::translate(model, glm::vec3(-29.0f, 0.0f, 12.0f));
		model = glm::scale(model, glm::vec3(8.0f, 8.0f, 8.0f));
		staticShader.setMat4("model", model);
		table.Draw(staticShader);
		//mesa bedroom2-1
		model = glm::rotate(glm::mat4(1.0f), glm::radians(0.0f), glm::vec3(1.0f, 0.0f, 0.0f));
		model = glm::translate(model, glm::vec3(-22.0f, 0.0f, -17.0f));
		model = glm::scale(model, glm::vec3(8.0f, 8.0f, 8.0f));
		staticShader.setMat4("model", model);
		table.Draw(staticShader);
		//mesa bedroom2-2
		model = glm::rotate(glm::mat4(1.0f), glm::radians(0.0f), glm::vec3(1.0f, 0.0f, 0.0f));
		model = glm::translate(model, glm::vec3(-8.0f, 0.0f, -17.0f));
		model = glm::scale(model, glm::vec3(8.0f, 8.0f, 8.0f));
		staticShader.setMat4("model", model);
		table.Draw(staticShader);
		//mesa family meals 1
		model = glm::rotate(glm::mat4(1.0f), glm::radians(0.0f), glm::vec3(1.0f, 0.0f, 0.0f));
		model = glm::translate(model, glm::vec3(5.0f, 0.5f, -140.0f));
		model = glm::scale(model, glm::vec3(0.15f, 0.15f, 0.15f));
		staticShader.setMat4("model", model);
		smallTable.Draw(staticShader);
		//mesa family meals 2
		model = glm::rotate(glm::mat4(1.0f), glm::radians(0.0f), glm::vec3(1.0f, 0.0f, 0.0f));
		model = glm::translate(model, glm::vec3(23.0f, 0.5f, -125.0f));
		model = glm::scale(model, glm::vec3(16.0f, 16.0f, 16.0f));
		staticShader.setMat4("model", model);
		basicTable.Draw(staticShader);
		//mesa alfresco
		model = glm::rotate(glm::mat4(1.0f), glm::radians(0.0f), glm::vec3(1.0f, 0.0f, 0.0f));
		model = glm::translate(model, glm::vec3(60.0f, 0.5f, -65.0f));
		model = glm::scale(model, glm::vec3(0.1f, 0.1f, 0.1f));
		staticShader.setMat4("model", model);
		patioTable.Draw(staticShader);
		//mesa living room
		model = glm::rotate(glm::mat4(1.0f), glm::radians(0.0f), glm::vec3(1.0f, 0.0f, 0.0f));
		model = glm::translate(model, glm::vec3(25.0f, 0.5f, -63.0f));
		model = glm::scale(model, glm::vec3(0.09f, 0.09f, 0.09f));
		model = glm::rotate(model, glm::radians(90.0f), glm::vec3(0.0f, 1.0f, 0.0));
		staticShader.setMat4("model", model);
		livinTable.Draw(staticShader);

		//sillones
		//sillon pequeño bedroom1
		model = glm::rotate(glm::mat4(1.0f), glm::radians(0.0f), glm::vec3(1.0f, 0.0f, 0.0f));
		model = glm::translate(model, glm::vec3(-5.0f, 0.5f, 30.0f));
		model = glm::scale(model, glm::vec3(2.0f, 2.0f, 2.0f));
		model = glm::rotate(model, glm::radians(245.0f), glm::vec3(0.0f, 1.0f, 0.0));
		staticShader.setMat4("model", model);
		smallSofa.Draw(staticShader);
		//sillon pequeño family meals
		model = glm::rotate(glm::mat4(1.0f), glm::radians(0.0f), glm::vec3(1.0f, 0.0f, 0.0f));
		model = glm::translate(model, glm::vec3(17.0f, 0.5f, -140.0f));
		model = glm::scale(model, glm::vec3(2.5f, 2.5f, 2.5f));
		//model = glm::rotate(model, glm::radians(245.0f), glm::vec3(0.0f, 1.0f, 0.0));
		staticShader.setMat4("model", model);
		smallSofa.Draw(staticShader);
		//sillon family meals
		model = glm::rotate(glm::mat4(1.0f), glm::radians(0.0f), glm::vec3(1.0f, 0.0f, 0.0f));
		model = glm::translate(model, glm::vec3(3.0f, 0.5f, -128.0f));
		model = glm::scale(model, glm::vec3(2.5f, 2.5f, 2.5f));
		model = glm::rotate(model, glm::radians(90.0f), glm::vec3(0.0f, 1.0f, 0.0));
		staticShader.setMat4("model", model);
		sofa.Draw(staticShader);
		//sillon living room 1
		model = glm::rotate(glm::mat4(1.0f), glm::radians(0.0f), glm::vec3(1.0f, 0.0f, 0.0f));
		model = glm::translate(model, glm::vec3(29.0f, 0.5f, -76.0f));
		model = glm::scale(model, glm::vec3(4.5f, 3.5f, 3.5f));
		//model = glm::rotate(model, glm::radians(90.0f), glm::vec3(0.0f, 1.0f, 0.0));
		staticShader.setMat4("model", model);
		sofa.Draw(staticShader);
		//sillon living room 2
		model = glm::rotate(glm::mat4(1.0f), glm::radians(0.0f), glm::vec3(1.0f, 0.0f, 0.0f));
		model = glm::translate(model, glm::vec3(29.0f, 0.5f, -50.0f));
		model = glm::scale(model, glm::vec3(2.5f, 2.5f, 2.5f));
		model = glm::rotate(model, glm::radians(180.0f), glm::vec3(0.0f, 1.0f, 0.0));
		staticShader.setMat4("model", model);
		sofa.Draw(staticShader);
		//sillon kidz zone
		model = glm::rotate(glm::mat4(1.0f), glm::radians(0.0f), glm::vec3(1.0f, 0.0f, 0.0f));
		model = glm::translate(model, glm::vec3(-19.0f, 0.5f, -47.0f));
		model = glm::scale(model, glm::vec3(3.5f, 3.5f, 3.5f));
		model = glm::rotate(model, glm::radians(180.0f), glm::vec3(0.0f, 1.0f, 0.0));
		staticShader.setMat4("model", model);
		sofa.Draw(staticShader);
		//sillon alfresco 1
		model = glm::rotate(glm::mat4(1.0f), glm::radians(0.0f), glm::vec3(1.0f, 0.0f, 0.0f));
		model = glm::translate(model, glm::vec3(55.0f, 0.5f, -90.0f));
		model = glm::scale(model, glm::vec3(3.0f, 3.0f, 3.0f));
		model = glm::rotate(model, glm::radians(135.0f), glm::vec3(0.0f, 1.0f, 0.0));
		staticShader.setMat4("model", model);
		alfSofa.Draw(staticShader);
		//sillon alfresco 2
		model = glm::rotate(glm::mat4(1.0f), glm::radians(0.0f), glm::vec3(1.0f, 0.0f, 0.0f));
		model = glm::translate(model, glm::vec3(70.0f, 0.5f, -90.0f));
		model = glm::scale(model, glm::vec3(3.0f, 3.0f, 3.0f));
		model = glm::rotate(model, glm::radians(225.0f), glm::vec3(0.0f, 1.0f, 0.0));
		staticShader.setMat4("model", model);
		alfSofa.Draw(staticShader);

		//Toilets
		//toilet bathroom 1
		model = glm::rotate(glm::mat4(1.0f), glm::radians(0.0f), glm::vec3(1.0f, 0.0f, 0.0f));
		model = glm::translate(model, glm::vec3(-11.0f, 0.5f, 0.0f));
		model = glm::scale(model, glm::vec3(6.0f, 6.0f, 6.0f));
		model = glm::rotate(model, glm::radians(270.0f), glm::vec3(0.0f, 1.0f, 0.0));
		staticShader.setMat4("model", model);
		toilet.Draw(staticShader);
		//toilet bathroom 2
		model = glm::rotate(glm::mat4(1.0f), glm::radians(0.0f), glm::vec3(1.0f, 0.0f, 0.0f));
		model = glm::translate(model, glm::vec3(-20.0f, 0.5f, -74.9f));
		model = glm::scale(model, glm::vec3(6.0f, 6.0f, 6.0f));
		model = glm::rotate(model, glm::radians(180.0f), glm::vec3(0.0f, 1.0f, 0.0));
		staticShader.setMat4("model", model);
		toilet.Draw(staticShader);

		//Lavamanos
		//lavamanos bathroom 1
		model = glm::rotate(glm::mat4(1.0f), glm::radians(0.0f), glm::vec3(1.0f, 0.0f, 0.0f));
		model = glm::translate(model, glm::vec3(-29.0f, 5.5f, -4.0f));
		model = glm::scale(model, glm::vec3(0.1f, 0.1f, 0.1f));
		model = glm::rotate(model, glm::radians(180.0f), glm::vec3(0.0f, 1.0f, 0.0));
		staticShader.setMat4("model", model);
		sink.Draw(staticShader);
		//Lavamanos bathroom 2
		model = glm::rotate(glm::mat4(1.0f), glm::radians(0.0f), glm::vec3(1.0f, 0.0f, 0.0f));
		model = glm::translate(model, glm::vec3(-20.0f, 5.5f, -92.0f));
		model = glm::scale(model, glm::vec3(0.1f, 0.1f, 0.1f));
		model = glm::rotate(model, glm::radians(90.0f), glm::vec3(0.0f, 1.0f, 0.0));
		staticShader.setMat4("model", model);
		sink.Draw(staticShader);
		//lavamanos laundry
		model = glm::rotate(glm::mat4(1.0f), glm::radians(0.0f), glm::vec3(1.0f, 0.0f, 0.0f));
		model = glm::translate(model, glm::vec3(-27.0f, 5.5f, -98.0f));
		model = glm::scale(model, glm::vec3(0.05f, 0.05f, 0.05f));
		model = glm::rotate(model, glm::radians(270.0f), glm::vec3(0.0f, 1.0f, 0.0));
		staticShader.setMat4("model", model);
		sink.Draw(staticShader);

		//Lavadora
		model = glm::rotate(glm::mat4(1.0f), glm::radians(0.0f), glm::vec3(1.0f, 0.0f, 0.0f));
		model = glm::translate(model, glm::vec3(-20.0f, 0.5f, -99.0f));
		model = glm::scale(model, glm::vec3(8.0f, 8.0f, 8.0f));
		model = glm::rotate(model, glm::radians(180.0f), glm::vec3(0.0f, 1.0f, 0.0));
		staticShader.setMat4("model", model);
		washing.Draw(staticShader);

		//Tina de baño
		model = glm::rotate(glm::mat4(1.0f), glm::radians(0.0f), glm::vec3(1.0f, 0.0f, 0.0f));
		model = glm::translate(model, glm::vec3(-29.0f, 0.5f, -83.0f));
		model = glm::scale(model, glm::vec3(0.06f, 0.06f, 0.06f));
		model = glm::rotate(model, glm::radians(90.0f), glm::vec3(0.0f, 1.0f, 0.0));
		staticShader.setMat4("model", model);
		bathtub.Draw(staticShader);

		//Teles
		//tele Kidz zone
		model = glm::rotate(glm::mat4(1.0f), glm::radians(0.0f), glm::vec3(1.0f, 0.0f, 0.0f));
		model = glm::translate(model, glm::vec3(-19.0f, 0.3f, -67.0f));
		model = glm::scale(model, glm::vec3(6.0f, 8.0f, 8.0f));
		model = glm::rotate(model, glm::radians(0.0f), glm::vec3(0.0f, 1.0f, 0.0));
		staticShader.setMat4("model", model);
		tv.Draw(staticShader);
		//Tele living room
		model = glm::rotate(glm::mat4(1.0f), glm::radians(0.0f), glm::vec3(1.0f, 0.0f, 0.0f));
		model = glm::translate(model, glm::vec3(2.5f, 0.3f, -72.2f));
		model = glm::scale(model, glm::vec3(6.0f, 6.0f, 6.0f));
		model = glm::rotate(model, glm::radians(90.0f), glm::vec3(0.0f, 1.0f, 0.0));
		staticShader.setMat4("model", model);
		tv.Draw(staticShader);

		//estufa
		model = glm::rotate(glm::mat4(1.0f), glm::radians(0.0f), glm::vec3(1.0f, 0.0f, 0.0f));
		model = glm::translate(model, glm::vec3(25.0f, 0.3f, -87.0f));
		model = glm::scale(model, glm::vec3(0.1f, 0.1f, 0.1f));
		model = glm::rotate(model, glm::radians(-90.0f), glm::vec3(0.0f, 1.0f, 0.0));
		staticShader.setMat4("model", model);
		estufa.Draw(staticShader);

		//tarja
		model = glm::rotate(glm::mat4(1.0f), glm::radians(0.0f), glm::vec3(1.0f, 0.0f, 0.0f));
		model = glm::translate(model, glm::vec3(40.5f, 0.3f, -89.0f));
		model = glm::scale(model, glm::vec3(0.1f, 0.1f, 0.1f));
		model = glm::rotate(model, glm::radians(90.0f), glm::vec3(0.0f, 1.0f, 0.0));
		staticShader.setMat4("model", model);
		tarja.Draw(staticShader);

		//barra
		model = glm::rotate(glm::mat4(1.0f), glm::radians(0.0f), glm::vec3(1.0f, 0.0f, 0.0f));
		model = glm::translate(model, glm::vec3(18.0f, 0.3f, -102.0f));
		model = glm::scale(model, glm::vec3(0.1f, 0.1f, 0.1f));
		model = glm::rotate(model, glm::radians(0.0f), glm::vec3(0.0f, 1.0f, 0.0));
		staticShader.setMat4("model", model);
		barra.Draw(staticShader);

		//carro
		model = glm::rotate(glm::mat4(1.0f), glm::radians(0.0f), glm::vec3(1.0f, 0.0f, 0.0f));
		model = glm::translate(model, glm::vec3(36.0f, 3.5f, -15.0f));
		model = glm::scale(model, glm::vec3(9.0f, 9.0f, 9.0f));
		model = glm::rotate(model, glm::radians(180.0f), glm::vec3(0.0f, 1.0f, 0.0));
		staticShader.setMat4("model", model);
		coche.Draw(staticShader);
		//Rasho Macuin
		model = glm::rotate(glm::mat4(1.0f), glm::radians(0.0f), glm::vec3(1.0f, 0.0f, 0.0f));
		model = glm::translate(model, glm::vec3(60.0f + cocheX, 0.5f, -13.0f + cocheZ));
		model = glm::scale(model, glm::vec3(8.0f, 8.0f, 8.0f));
		model = glm::rotate(model, glm::radians(0.0f + rotCocheY), glm::vec3(0.0f, 1.0f, 0.0));
		staticShader.setMat4("model", model);
		rasho.Draw(staticShader);

		//alberca
		model = glm::rotate(glm::mat4(1.0f), glm::radians(0.0f), glm::vec3(1.0f, 0.0f, 0.0f));
		model = glm::translate(model, glm::vec3(65.0f, 5.5f, -160.0f));
		model = glm::scale(model, glm::vec3(0.4f, 0.4f, 0.4f));
		model = glm::rotate(model, glm::radians(-90.0f), glm::vec3(1.0f, 0.0f, 0.0));
		model = glm::rotate(model, glm::radians(-90.0f), glm::vec3(0.0f, 0.0f, 1.0));
		staticShader.setMat4("model", model);
		pool.Draw(staticShader);

		//tablon en skate
		model = glm::rotate(glm::mat4(1.0f), glm::radians(0.0f), glm::vec3(1.0f, 0.0f, 0.0f));
		model = glm::translate(model, glm::vec3(95.0f, 0.3f + skateY, 13.0f + skateZ));
		model = glm::scale(model, glm::vec3(2.0f, 2.0f, 2.0f));
		model = glm::rotate(model, glm::radians(-90.0f + skaterotY), glm::vec3(0.0f, 1.0f, 0.0));
		tmp = model = glm::rotate(model, glm::radians(0.0f + skateRotZ), glm::vec3(0.0f, 0.0f, 1.0));
		staticShader.setMat4("model", model);
		skate.Draw(staticShader);
		model = glm::translate(tmp, glm::vec3(0.0f, 4.0f, 0.0f));
		model = glm::scale(model, glm::vec3(1.0f, 1.0f, 1.0f));
		model = glm::rotate(model, glm::radians(180.0f + rotTablonY), glm::vec3(0.0f, 1.0f, 0.0f));
		staticShader.setMat4("model", model);
		tablon.Draw(staticShader);

		//rampa 1
		model = glm::rotate(glm::mat4(1.0f), glm::radians(0.0f), glm::vec3(1.0f, 0.0f, 0.0f));
		model = glm::translate(model, glm::vec3(95.0f, 0.3f, -38.0f));
		model = glm::scale(model, glm::vec3(2.0f, 2.0f, 2.0f));
		model = glm::rotate(model, glm::radians(-90.0f), glm::vec3(0.0f, 1.0f, 0.0));
		staticShader.setMat4("model", model);
		ramp.Draw(staticShader);

		//rampa 2
		model = glm::rotate(glm::mat4(1.0f), glm::radians(0.0f), glm::vec3(1.0f, 0.0f, 0.0f));
		model = glm::translate(model, glm::vec3(95.0f, 0.3f, -86.0f));
		model = glm::scale(model, glm::vec3(2.0f, 2.0f, 2.0f));
		model = glm::rotate(model, glm::radians(90.0f), glm::vec3(0.0f, 1.0f, 0.0));
		staticShader.setMat4("model", model);
		ramp.Draw(staticShader);

		//Arboles

		//Arboles cerca de la casa principal
		//Arbol 1
		model = glm::rotate(glm::mat4(1.0f), glm::radians(0.0f), glm::vec3(1.0f, 0.0f, 0.0f));
		model = glm::translate(model, glm::vec3(-35.0f, 0.5f, 60.0f));
		model = glm::scale(model, glm::vec3(0.3f, 0.3f, 0.3f));
		model = glm::rotate(model, glm::radians(180.0f), glm::vec3(0.0f, 1.0f, 0.0));
		staticShader.setMat4("model", model);
		tree.Draw(staticShader);

		//Arbol 2
		model = glm::rotate(glm::mat4(1.0f), glm::radians(0.0f), glm::vec3(1.0f, 0.0f, 0.0f));
		model = glm::translate(model, glm::vec3(-49.0f, 0.5f, 0.0f));
		model = glm::scale(model, glm::vec3(0.3f, 0.3f, 0.3f));
		model = glm::rotate(model, glm::radians(180.0f), glm::vec3(0.0f, 1.0f, 0.0));
		staticShader.setMat4("model", model);
		tree.Draw(staticShader);

		//Arbol 3
		model = glm::rotate(glm::mat4(1.0f), glm::radians(0.0f), glm::vec3(1.0f, 0.0f, 0.0f));
		model = glm::translate(model, glm::vec3(-49.0f, 0.5f, -155.0f));
		model = glm::scale(model, glm::vec3(0.3f, 0.3f, 0.3f));
		model = glm::rotate(model, glm::radians(180.0f), glm::vec3(0.0f, 1.0f, 0.0));
		staticShader.setMat4("model", model);
		tree.Draw(staticShader);

		//Arbol 4
		model = glm::rotate(glm::mat4(1.0f), glm::radians(0.0f), glm::vec3(1.0f, 0.0f, 0.0f));
		model = glm::translate(model, glm::vec3(60.0f, 0.5f, -190.0f));
		model = glm::scale(model, glm::vec3(0.3f, 0.3f, 0.3f));
		model = glm::rotate(model, glm::radians(180.0f), glm::vec3(0.0f, 1.0f, 0.0));
		staticShader.setMat4("model", model);
		tree.Draw(staticShader);

		//arbol con columpio
		model = glm::rotate(glm::mat4(1.0f), glm::radians(0.0f), glm::vec3(1.0f, 0.0f, 0.0f));
		model = glm::translate(model, glm::vec3(100.0f, 0.5f, -160.0f));
		model = glm::scale(model, glm::vec3(0.5f, 0.5f, 0.5f));
		tmp = model = glm::rotate(model, glm::radians(-90.0f), glm::vec3(0.0f, 1.0f, 0.0));
		staticShader.setMat4("model", model);
		tree.Draw(staticShader);
		model = glm::translate(tmp, glm::vec3(20.0f, 20.0f, 0.0f));
		model = glm::scale(model, glm::vec3(0.2f, 0.2f, 0.2f));
		model = glm::rotate(model, glm::radians(90.0f), glm::vec3(1.0f, 0.0f, 0.0f));
		model = glm::rotate(model, glm::radians(180.0f), glm::vec3(0.0f, 1.0f, 0.0f));
		model = glm::rotate(model, glm::radians(180.0f + rotSwingY), glm::vec3(0.0f, 0.0f, 1.0f));
		staticShader.setMat4("model", model);
		swing.Draw(staticShader);

		//arboles en el vecindario
		//Arbol 1
		model = glm::rotate(glm::mat4(1.0f), glm::radians(0.0f), glm::vec3(1.0f, 0.0f, 0.0f));
		model = glm::translate(model, glm::vec3(160.0f, 0.0f, 400.0f));
		model = glm::scale(model, glm::vec3(0.3f, 0.3f, 0.3f));
		model = glm::rotate(model, glm::radians(180.0f), glm::vec3(0.0f, 1.0f, 0.0));
		staticShader.setMat4("model", model);
		tree.Draw(staticShader);

		//Arbol 2
		model = glm::rotate(glm::mat4(1.0f), glm::radians(0.0f), glm::vec3(1.0f, 0.0f, 0.0f));
		model = glm::translate(model, glm::vec3(140.0f, 0.0f, 100.0f));
		model = glm::scale(model, glm::vec3(0.3f, 0.3f, 0.3f));
		model = glm::rotate(model, glm::radians(180.0f), glm::vec3(0.0f, 1.0f, 0.0));
		staticShader.setMat4("model", model);
		tree.Draw(staticShader);


		//Arbol 3
		model = glm::rotate(glm::mat4(1.0f), glm::radians(0.0f), glm::vec3(1.0f, 0.0f, 0.0f));
		model = glm::translate(model, glm::vec3(130.0f, 0.5f, 240.0f));
		model = glm::scale(model, glm::vec3(0.3f, 0.3f, 0.3f));
		model = glm::rotate(model, glm::radians(180.0f), glm::vec3(0.0f, 1.0f, 0.0));
		staticShader.setMat4("model", model);
		tree.Draw(staticShader);


		//Arbol 4
		model = glm::rotate(glm::mat4(1.0f), glm::radians(0.0f), glm::vec3(1.0f, 0.0f, 0.0f));
		model = glm::translate(model, glm::vec3(-160.0f, 0.0f, 400.0f));
		model = glm::scale(model, glm::vec3(0.3f, 0.3f, 0.3f));
		model = glm::rotate(model, glm::radians(180.0f), glm::vec3(0.0f, 1.0f, 0.0));
		staticShader.setMat4("model", model);
		tree.Draw(staticShader);

		//Arbol 5
		model = glm::rotate(glm::mat4(1.0f), glm::radians(0.0f), glm::vec3(1.0f, 0.0f, 0.0f));
		model = glm::translate(model, glm::vec3(-140.0f, 0.0f, 100.0f));
		model = glm::scale(model, glm::vec3(0.3f, 0.3f, 0.3f));
		model = glm::rotate(model, glm::radians(180.0f), glm::vec3(0.0f, 1.0f, 0.0));
		staticShader.setMat4("model", model);
		tree.Draw(staticShader);

		//Arbol 6
		model = glm::rotate(glm::mat4(1.0f), glm::radians(0.0f), glm::vec3(1.0f, 0.0f, 0.0f));
		model = glm::translate(model, glm::vec3(-130.0f, 0.5f, 240.0f));
		model = glm::scale(model, glm::vec3(0.3f, 0.3f, 0.3f));
		model = glm::rotate(model, glm::radians(180.0f), glm::vec3(0.0f, 1.0f, 0.0));
		staticShader.setMat4("model", model);
		tree.Draw(staticShader);

		//modelo kid
		//body
		model = glm::rotate(glm::mat4(1.0f), glm::radians(0.0f), glm::vec3(1.0f, 0.0f, 0.0f));
		model = glm::translate(model, glm::vec3(110.0f + kidposX, 0.0f + kidposY, -140.0f + kidposZ));
		model = glm::scale(model, glm::vec3(1.0f, 1.0f, 1.0f));
		tmp = model = glm::rotate(model, glm::radians(-90.0f + movcuerpo), glm::vec3(0.0f, 1.0f, 0.0));
		staticShader.setMat4("model", model);
		kidBody.Draw(staticShader);
		//head
		model = glm::translate(tmp, glm::vec3(0.25f, 1.7f, -0.5f));
		model = glm::rotate(model, glm::radians(movCabezaKid), glm::vec3(0.0f, 1.0f, 0.0));
		model = glm::translate(model, glm::vec3(0.0f, 3.5f, 0));
		staticShader.setMat4("model", model);
		kidHead.Draw(staticShader);
		//r_arm
		model = glm::translate(tmp, glm::vec3(0.0f, 2.6f, 0.0f));
		model = glm::translate(model, glm::vec3(-0.2f, 2.5f, -1.0f));
		model = glm::rotate(model, glm::radians(movbrazoDer), glm::vec3(0.0f, 1.0f, 0.0f));
		staticShader.setMat4("model", model);
		kidR_arm.Draw(staticShader);
		//l_arm
		model = glm::translate(tmp, glm::vec3(0.0f, 2.7f, 0.0f));
		model = glm::translate(model, glm::vec3(0.55f, 2.5f, -1.0f));
		model = glm::rotate(model, glm::radians(movbrazoIzq), glm::vec3(0.0f, 1.0f, 0.0f));
		staticShader.setMat4("model", model);
		kidL_arm.Draw(staticShader);
		//r_leg
		model = glm::translate(tmp, glm::vec3(-0.5f, 2.0f, -0.1f));
		model = glm::rotate(model, glm::radians(0.0f), glm::vec3(0.0f, 1.0f, 0.0));
		model = glm::rotate(model, glm::radians(-movpieDer), glm::vec3(1.0f, 0.0f, 0.0f));
		staticShader.setMat4("model", model);
		kidR_leg.Draw(staticShader);
		//l_leg
		model = glm::translate(tmp, glm::vec3(1.0f, 1.6f, -0.1f));
		model = glm::rotate(model, glm::radians(0.0f), glm::vec3(0.0f, 1.0f, 0.0));
		model = glm::rotate(model, glm::radians(-movpieIzq), glm::vec3(1.0f, 0.0f, 0.0f));
		staticShader.setMat4("model", model);
		kidL_leg.Draw(staticShader);
		//ball
		model = glm::translate(tmp, glm::vec3(2.0f, 0.6f, 3.0f));
		model = glm::scale(model, glm::vec3(0.03f, 0.03f, 0.03f));
		model = glm::rotate(model, glm::radians(0.0f), glm::vec3(0.0f, 1.0f, 0.0));
		model = glm::rotate(model, glm::radians(movBalon), glm::vec3(1.0f, 0.0f, 0.0f));
		staticShader.setMat4("model", model);
		kidBall.Draw(staticShader);

		//modelo gato
		//body
		model = glm::rotate(glm::mat4(1.0f), glm::radians(0.0f), glm::vec3(1.0f, 0.0f, 0.0f));
		model = glm::translate(model, glm::vec3(-20.0f + posX, 7.0f + posY, 23.0f + posZ));
		model = glm::scale(model, glm::vec3(1.0f, 1.0f, 1.0f));
		tmp = model = glm::rotate(model, glm::radians(movTorso), glm::vec3(0.0f, 1.0f, 0.0));
		staticShader.setMat4("model", model);
		catBody.Draw(staticShader);
		//head
		model = glm::translate(tmp, glm::vec3(0.0f, -3.1f, 1.4f));
		model = glm::rotate(model, glm::radians(movCabeza), glm::vec3(0.0f, 1.0f, 0.0));
		model = glm::translate(model, glm::vec3(0.0f, 3.5f, 0));
		staticShader.setMat4("model", model);
		catHead.Draw(staticShader);
		//r_arm
		model = glm::translate(tmp, glm::vec3(0.0f, 2.5f, 0.0f));
		model = glm::translate(model, glm::vec3(-0.35f, -2.5f, 0.9f));
		model = glm::rotate(model, glm::radians(rotpatader), glm::vec3(1.0f, 0.0f, 0.0f));
		staticShader.setMat4("model", model);
		catR_arm.Draw(staticShader);
		//l_arm
		model = glm::translate(tmp, glm::vec3(0.0f, 2.7f, 0.0f));
		model = glm::translate(model, glm::vec3(0.5f, -2.5f, 0.9f));
		model = glm::rotate(model, glm::radians(rotpataizq), glm::vec3(1.0f, 0.0f, 0.0f));
		staticShader.setMat4("model", model);
		catL_arm.Draw(staticShader);
		//r_leg
		model = glm::translate(tmp, glm::vec3(0.0f, 2.5f, 0.0f));
		model = glm::translate(model, glm::vec3(-0.35f, -2.7f, -1.0f));
		model = glm::rotate(model, glm::radians(rotpardertra), glm::vec3(1.0f, 0.0f, 0.0f));
		staticShader.setMat4("model", model);
		catR_leg.Draw(staticShader);
		//l-leg
		model = glm::translate(tmp, glm::vec3(0.0f, 2.5f, 0.0f));
		model = glm::translate(model, glm::vec3(0.5f, -2.5f, -1.0f));
		model = glm::rotate(model, glm::radians(rotparizqtra), glm::vec3(1.0f, 0.0f, 0.0f));
		staticShader.setMat4("model", model);
		catL_leg.Draw(staticShader);
		//tail
		model = glm::translate(tmp, glm::vec3(0.0f, -2.9f, -1.5f));
		model = glm::rotate(model, glm::radians(movCola), glm::vec3(0.0f, 1.0f, 0.0));
		model = glm::translate(model, glm::vec3(0.0f, 3.5f, 0));
		staticShader.setMat4("model", model);
		catTail.Draw(staticShader);

		//cercas
		//cerca1
		model = glm::rotate(glm::mat4(1.0f), glm::radians(00.0f), glm::vec3(1.0f, 0.0f, 0.0f));
		model = glm::translate(model, glm::vec3(120.0f, 14.0f, 375.0f));
		model = glm::scale(model, glm::vec3(0.2f, 0.2f, 0.2f));
		model = glm::rotate(model, glm::radians(90.0f), glm::vec3(0.0f, 0.0f, 1.0));
		tmp = model = glm::rotate(model, glm::radians(-90.0f), glm::vec3(0.0f, 1.0f, 0.0));
		staticShader.setMat4("model", model);
		cerca.Draw(staticShader);
		model = glm::translate(tmp, glm::vec3(0.0f, -130.0f, 0.0f));
		model = glm::rotate(model, glm::radians(0.0f), glm::vec3(0.0f, 0.0f, 1.0f));
		staticShader.setMat4("model", model);
		cerca.Draw(staticShader);
		model = glm::translate(tmp, glm::vec3(0.0f, -260.0f, 0.0f));
		model = glm::rotate(model, glm::radians(0.0f), glm::vec3(0.0f, 0.0f, 1.0f));
		staticShader.setMat4("model", model);
		cerca.Draw(staticShader);
		model = glm::translate(tmp, glm::vec3(0.0f, -390.0f, 0.0f));
		model = glm::rotate(model, glm::radians(0.0f), glm::vec3(0.0f, 0.0f, 1.0f));
		staticShader.setMat4("model", model);
		cerca.Draw(staticShader);
		model = glm::translate(tmp, glm::vec3(0.0f, -520.0f, 0.0f));
		model = glm::rotate(model, glm::radians(0.0f), glm::vec3(0.0f, 0.0f, 1.0f));
		staticShader.setMat4("model", model);
		cerca.Draw(staticShader);
		model = glm::translate(tmp, glm::vec3(0.0f, -650.0f, 0.0f));
		model = glm::rotate(model, glm::radians(0.0f), glm::vec3(0.0f, 0.0f, 1.0f));
		staticShader.setMat4("model", model);
		cerca.Draw(staticShader);
		//cerca2
		model = glm::rotate(glm::mat4(1.0f), glm::radians(00.0f), glm::vec3(1.0f, 0.0f, 0.0f));
		model = glm::translate(model, glm::vec3(-225.0f, 14.0f, 375.0f));
		model = glm::scale(model, glm::vec3(0.2f, 0.2f, 0.2f));
		model = glm::rotate(model, glm::radians(90.0f), glm::vec3(0.0f, 0.0f, 1.0));
		tmp = model = glm::rotate(model, glm::radians(-90.0f), glm::vec3(0.0f, 1.0f, 0.0));
		staticShader.setMat4("model", model);
		cerca.Draw(staticShader);
		model = glm::translate(tmp, glm::vec3(0.0f, -130.0f, 0.0f));
		model = glm::rotate(model, glm::radians(0.0f), glm::vec3(0.0f, 0.0f, 1.0f));
		staticShader.setMat4("model", model);
		cerca.Draw(staticShader);
		model = glm::translate(tmp, glm::vec3(0.0f, -260.0f, 0.0f));
		model = glm::rotate(model, glm::radians(0.0f), glm::vec3(0.0f, 0.0f, 1.0f));
		staticShader.setMat4("model", model);
		cerca.Draw(staticShader);
		model = glm::translate(tmp, glm::vec3(0.0f, -390.0f, 0.0f));
		model = glm::rotate(model, glm::radians(0.0f), glm::vec3(0.0f, 0.0f, 1.0f));
		staticShader.setMat4("model", model);
		cerca.Draw(staticShader);
		model = glm::translate(tmp, glm::vec3(0.0f, -520.0f, 0.0f));
		model = glm::rotate(model, glm::radians(0.0f), glm::vec3(0.0f, 0.0f, 1.0f));
		staticShader.setMat4("model", model);
		cerca.Draw(staticShader);
		model = glm::translate(tmp, glm::vec3(0.0f, -650.0f, 0.0f));
		model = glm::rotate(model, glm::radians(0.0f), glm::vec3(0.0f, 0.0f, 1.0f));
		staticShader.setMat4("model", model);
		cerca.Draw(staticShader);
		//cerca3
		model = glm::rotate(glm::mat4(1.0f), glm::radians(00.0f), glm::vec3(1.0f, 0.0f, 0.0f));
		model = glm::translate(model, glm::vec3(-225.0f, 14.0f, 257.0f));
		model = glm::scale(model, glm::vec3(0.2f, 0.2f, 0.2f));
		model = glm::rotate(model, glm::radians(90.0f), glm::vec3(0.0f, 0.0f, 1.0));
		tmp = model = glm::rotate(model, glm::radians(-90.0f), glm::vec3(0.0f, 1.0f, 0.0));
		staticShader.setMat4("model", model);
		cerca.Draw(staticShader);
		model = glm::translate(tmp, glm::vec3(0.0f, -130.0f, 0.0f));
		model = glm::rotate(model, glm::radians(0.0f), glm::vec3(0.0f, 0.0f, 1.0f));
		staticShader.setMat4("model", model);
		cerca.Draw(staticShader);
		model = glm::translate(tmp, glm::vec3(0.0f, -260.0f, 0.0f));
		model = glm::rotate(model, glm::radians(0.0f), glm::vec3(0.0f, 0.0f, 1.0f));
		staticShader.setMat4("model", model);
		cerca.Draw(staticShader);
		model = glm::translate(tmp, glm::vec3(0.0f, -390.0f, 0.0f));
		model = glm::rotate(model, glm::radians(0.0f), glm::vec3(0.0f, 0.0f, 1.0f));
		staticShader.setMat4("model", model);
		cerca.Draw(staticShader);
		model = glm::translate(tmp, glm::vec3(0.0f, -520.0f, 0.0f));
		model = glm::rotate(model, glm::radians(0.0f), glm::vec3(0.0f, 0.0f, 1.0f));
		staticShader.setMat4("model", model);
		cerca.Draw(staticShader);
		model = glm::translate(tmp, glm::vec3(0.0f, -650.0f, 0.0f));
		model = glm::rotate(model, glm::radians(0.0f), glm::vec3(0.0f, 0.0f, 1.0f));
		staticShader.setMat4("model", model);
		cerca.Draw(staticShader);
		//cerca4
		model = glm::rotate(glm::mat4(1.0f), glm::radians(00.0f), glm::vec3(1.0f, 0.0f, 0.0f));
		model = glm::translate(model, glm::vec3(120.0f, 14.0f, 257.0f));
		model = glm::scale(model, glm::vec3(0.2f, 0.2f, 0.2f));
		model = glm::rotate(model, glm::radians(90.0f), glm::vec3(0.0f, 0.0f, 1.0));
		tmp = model = glm::rotate(model, glm::radians(-90.0f), glm::vec3(0.0f, 1.0f, 0.0));
		staticShader.setMat4("model", model);
		cerca.Draw(staticShader);
		model = glm::translate(tmp, glm::vec3(0.0f, -130.0f, 0.0f));
		model = glm::rotate(model, glm::radians(0.0f), glm::vec3(0.0f, 0.0f, 1.0f));
		staticShader.setMat4("model", model);
		cerca.Draw(staticShader);
		model = glm::translate(tmp, glm::vec3(0.0f, -260.0f, 0.0f));
		model = glm::rotate(model, glm::radians(0.0f), glm::vec3(0.0f, 0.0f, 1.0f));
		staticShader.setMat4("model", model);
		cerca.Draw(staticShader);
		model = glm::translate(tmp, glm::vec3(0.0f, -390.0f, 0.0f));
		model = glm::rotate(model, glm::radians(0.0f), glm::vec3(0.0f, 0.0f, 1.0f));
		staticShader.setMat4("model", model);
		cerca.Draw(staticShader);
		model = glm::translate(tmp, glm::vec3(0.0f, -520.0f, 0.0f));
		model = glm::rotate(model, glm::radians(0.0f), glm::vec3(0.0f, 0.0f, 1.0f));
		staticShader.setMat4("model", model);
		cerca.Draw(staticShader);
		model = glm::translate(tmp, glm::vec3(0.0f, -650.0f, 0.0f));
		model = glm::rotate(model, glm::radians(0.0f), glm::vec3(0.0f, 0.0f, 1.0f));
		staticShader.setMat4("model", model);
		cerca.Draw(staticShader);


		//bancos
		//banco1
		model = glm::translate(glm::mat4(1.0f), glm::vec3(100.0f, 4.0f, 340.0f));
		model = glm::scale(model, glm::vec3(0.02f, 0.02f, 0.02f));
		model = glm::rotate(model, glm::radians(-180.0f), glm::vec3(1.0f, 0.0f, 0.0f));
		model = glm::rotate(model, glm::radians(115.0f), glm::vec3(0.0f, 0.0f, 1.0f));
		model = glm::rotate(model, glm::radians(0.0f), glm::vec3(0.0f, 1.0f, 0.0f));
		staticShader.setMat4("model", model);
		bench.Draw(staticShader);
		//banco2
		model = glm::translate(glm::mat4(1.0f), glm::vec3(-100.0f, 4.0f, 345.0f));
		model = glm::scale(model, glm::vec3(0.02f, 0.02f, 0.02f));
		model = glm::rotate(model, glm::radians(-180.0f), glm::vec3(1.0f, 0.0f, 0.0f));
		model = glm::rotate(model, glm::radians(-115.0f), glm::vec3(0.0f, 0.0f, 1.0f));
		model = glm::rotate(model, glm::radians(180.0f), glm::vec3(0.0f, 1.0f, 0.0f));
		staticShader.setMat4("model", model);
		bench.Draw(staticShader);
		//banco3
		model = glm::translate(glm::mat4(1.0f), glm::vec3(-140.0f, 4.0f, 170.0f));
		model = glm::scale(model, glm::vec3(0.02f, 0.02f, 0.02f));
		model = glm::rotate(model, glm::radians(-180.0f), glm::vec3(1.0f, 0.0f, 0.0f));
		model = glm::rotate(model, glm::radians(-115.0f), glm::vec3(0.0f, 0.0f, 1.0f));
		model = glm::rotate(model, glm::radians(180.0f), glm::vec3(0.0f, 1.0f, 0.0f));
		staticShader.setMat4("model", model);
		bench.Draw(staticShader);
		//banco4
		model = glm::translate(glm::mat4(1.0f), glm::vec3(150.0f, 4.0f, 170.0f));
		model = glm::scale(model, glm::vec3(0.02f, 0.02f, 0.02f));
		model = glm::rotate(model, glm::radians(-180.0f), glm::vec3(1.0f, 0.0f, 0.0f));
		model = glm::rotate(model, glm::radians(115.0f), glm::vec3(0.0f, 0.0f, 1.0f));
		model = glm::rotate(model, glm::radians(0.0f), glm::vec3(0.0f, 1.0f, 0.0f));
		staticShader.setMat4("model", model);
		bench.Draw(staticShader);

		//columpios
		//columpio1
		model = glm::translate(glm::mat4(1.0f), glm::vec3(110.0f, 1.0f, 40.0f));
		model = glm::scale(model, glm::vec3(10.0f, 1.0f, 1.0f));
		//model = glm::rotate(model, glm::radians(-180.0f), glm::vec3(1.0f, 0.0f, 0.0f));
		//model = glm::rotate(model, glm::radians(115.0f), glm::vec3(0.0f, 0.0f, 1.0f));
		model = glm::rotate(model, glm::radians(-90.0f), glm::vec3(0.0f, 1.0f, 0.0f));
		staticShader.setMat4("model", model);
		columpio.Draw(staticShader);
		//columpio2
		model = glm::translate(glm::mat4(1.0f), glm::vec3(-80.0f, 1.0f, 50.0f));
		model = glm::scale(model, glm::vec3(10.0f, 1.0f, 1.0f));
		//model = glm::rotate(model, glm::radians(-180.0f), glm::vec3(1.0f, 0.0f, 0.0f));
		//model = glm::rotate(model, glm::radians(115.0f), glm::vec3(0.0f, 0.0f, 1.0f));
		model = glm::rotate(model, glm::radians(-90.0f), glm::vec3(0.0f, 1.0f, 0.0f));
		staticShader.setMat4("model", model);
		columpio.Draw(staticShader);


		//telefono
		//base
		model = glm::rotate(glm::mat4(1.0f), glm::radians(0.0f), glm::vec3(1.0f, 0.0f, 0.0f));
		model = glm::translate(model, glm::vec3(25.0f, 8.0f, -65.0f));
		model = glm::scale(model, glm::vec3(0.5f, 0.5f, 0.5f));
		tmp = model = glm::rotate(model, glm::radians(0.0f), glm::vec3(0.0f, 1.0f, 0.0));
		staticShader.setMat4("model", model);
		telephoneBase.Draw(staticShader);
		model = glm::translate(tmp, glm::vec3(0.0f, 4.0f, -2.0f));
		model = glm::rotate(model, glm::radians(0.0f + rotPhone), glm::vec3(0.0f, 0.0f, 1.0f));
		staticShader.setMat4("model", model);
		telephone.Draw(staticShader);

		//| tele
		if (animTele) {
			tiempoTele++;
			musicFondo = false;
			musicTele = true;
			if (tiempoTele >= 0 && tiempoTele <= 60) {
				model = glm::rotate(glm::mat4(1.0f), glm::radians(0.0f), glm::vec3(1.0f, 0.0f, 0.0f));
				model = glm::translate(model, glm::vec3(-19.0f, 10.0f, -67.0f));
				model = glm::scale(model, glm::vec3(0.1f, 0.1f, 0.1f));
				model = glm::rotate(model, glm::radians(0.0f), glm::vec3(0.0f, 1.0f, 0.0));
				staticShader.setMat4("model", model);
				tele1.Draw(staticShader);
			}


			if (tiempoTele > 60 && tiempoTele <= 600) {
				model = glm::rotate(glm::mat4(1.0f), glm::radians(0.0f), glm::vec3(1.0f, 0.0f, 0.0f));
				model = glm::translate(model, glm::vec3(-19.0f, 10.0f, -67.0f));
				model = glm::scale(model, glm::vec3(0.1f, 0.1f, 0.1f));
				model = glm::rotate(model, glm::radians(0.0f), glm::vec3(0.0f, 1.0f, 0.0));
				staticShader.setMat4("model", model);
				tele2.Draw(staticShader);
			}

			if (tiempoTele > 600 && tiempoTele <= 1140) {
				model = glm::rotate(glm::mat4(1.0f), glm::radians(0.0f), glm::vec3(1.0f, 0.0f, 0.0f));
				model = glm::translate(model, glm::vec3(-19.0f, 10.0f, -67.0f));
				model = glm::scale(model, glm::vec3(0.1f, 0.1f, 0.1f));
				model = glm::rotate(model, glm::radians(0.0f), glm::vec3(0.0f, 1.0f, 0.0));
				staticShader.setMat4("model", model);
				tele3.Draw(staticShader);
			}

			if (tiempoTele > 1140 && tiempoTele <= 1680) {
				model = glm::rotate(glm::mat4(1.0f), glm::radians(0.0f), glm::vec3(1.0f, 0.0f, 0.0f));
				model = glm::translate(model, glm::vec3(-19.0f, 10.0f, -67.0f));
				model = glm::scale(model, glm::vec3(0.1f, 0.1f, 0.1f));
				model = glm::rotate(model, glm::radians(0.0f), glm::vec3(0.0f, 1.0f, 0.0));
				staticShader.setMat4("model", model);
				tele4.Draw(staticShader);
			}

			if (tiempoTele > 1680 && tiempoTele <= 1740) {
				model = glm::rotate(glm::mat4(1.0f), glm::radians(0.0f), glm::vec3(1.0f, 0.0f, 0.0f));
				model = glm::translate(model, glm::vec3(-19.0f, 10.0f, -67.0f));
				model = glm::scale(model, glm::vec3(0.1f, 0.1f, 0.1f));
				model = glm::rotate(model, glm::radians(0.0f), glm::vec3(0.0f, 1.0f, 0.0));
				staticShader.setMat4("model", model);
				tele1.Draw(staticShader);
			}
			if (tiempoTele > 1740) {
				animTele = false;
				tiempoTele = 0;
				musicFondo = true;
				musicTele = false;
			}


		}

		if (ringPhone) {
			if (ringIda) {
				rotPhone += 10.0;
				if (rotPhone > 25) {
					ringIda = false;
					ringRegreso = true;
				}
			}
			else {
				rotPhone -= 10.0;
				if (rotPhone < -25) {
					ringIda = true;
					ringRegreso = false;
				}
			}
		}
		else {
			rotPhone = 0;
			ringIda = false;
			ringRegreso = false;
		}

		//musica
		if (musicFondo) {
			engine->setAllSoundsPaused(false);
		}
		else {
			engine->setAllSoundsPaused(true);
		}
		if (musicTele) {
			engine2->setAllSoundsPaused(false);
		}
		else {
			engine2->setAllSoundsPaused(true);
		}



		/*if (ambiental)
			ambiental->setVolume(0.0005);*/








			// -------------------------------------------------------------------------------------------------------------------------
			// Termina Escenario
			// -------------------------------------------------------------------------------------------------------------------------

			//-------------------------------------------------------------------------------------
			// draw skybox as last
			// -------------------
		skyboxShader.use();
		//skybox.Draw(skyboxShader, view, projection, camera);


		// Limitar el framerate a 60
		deltaTime = SDL_GetTicks() - lastFrame; // time for full 1 loop
		//std::cout <<"frame time = " << frameTime << " milli sec"<< std::endl;
		if (deltaTime < LOOP_TIME)
		{
			SDL_Delay((int)(LOOP_TIME - deltaTime));
		}
		if (tiempo == 0) {
			//skybox = Skybox(faces);
			skybox.Draw(skyboxShader, view, projection, camera);

		}
		else {
			//skybox = Skybox(nightFaces);
			skybox2.Draw(skyboxShader, view, projection, camera);

		}

		//animacion tablon
		if (ida) {
			skateZ -= 0.9;

			rotTablonY = 0;
			if (skateZ <= -50 && skateZ > -75) {
				skateY++;
				skateRotZ -= 6.48;
			}
			if (skateZ <= -75 && skateZ > -100) {
				skateY--;
				skateRotZ -= 6.48;
			}
			if (skateZ <= -100) {
				skateY = 0;
				skateRotZ = 0;
			}
			if (skateZ <= -150) {
				ida = false;
				skaterotY = 180;
			}
		}
		else {
			skateZ += 0.9;
			if (skateZ >= -100 && skateZ < -75) {
				skateY++;
				skateRotZ -= 6.48;
			}
			if (skateZ >= -75 && skateZ < -50) {
				skateY--;
				skateRotZ -= 6.48;
			}
			if (skateZ >= -50) {
				skateY = 0;
				skateRotZ = 0;
			}
			rotTablonY = -180;
			if (skateZ >= 0) {
				ida = true;
				skaterotY = 0;
			}
		}

		//animacion coche
		if (cocheIda) {
			if (cocheZ < 70) {
				cocheZ += 0.5;
			}
			else {
				rotCocheY = -90;
				if (cocheX > -45) {
					cocheX -= 0.5;
				}
				else {
					cocheIda = false;
					permisoRegreso = true;
				}
			}
		}

		if (cocheRegreso) {
			if (cocheX < 0) {
				cocheX += 0.5;
			}
			else {
				rotCocheY = 0;
				if (cocheZ > 0) {
					cocheZ -= 0.5;
				}
				else {
					cocheRegreso = false;
					permisoIda = true;
				}
			}
		}

		//animacion columpio
		if (vuelta) {
			rotSwingY += 0.2;
			if (rotSwingY >= 180) {
				vuelta = false;
			}
		}
		else {
			rotSwingY -= 0.2;
			if (rotSwingY <= 0) {
				vuelta = true;
			}
		}

		if (reco) {
			camera = (glm::vec3(xIni + xAvance, yIni + yAvance, zIni + zAvance));

			if (reco1) {
				zAvance -= 1.0;
				if (zAvance <= -400) {
					reco1 = false;
					reco2 = true;

				}
			}
			if (reco2) {
				xAvance += 0.5;
				if (xAvance >= 75) {
					reco2 = false;
					reco3 = true;
				}
			}
			if (reco3) {
				zAvance -= 1.0;
				if (zAvance <= -650) {
					reco3 = false;
					reco4 = true;

				}
			}
			if (reco4) {
				xAvance += 0.5;
				if (xAvance >= 150) {
					reco4 = false;
					reco = false;
				}
			}
		}



		// glfw: swap buffers and poll IO events (keys pressed/released, mouse moved etc.)
		// -------------------------------------------------------------------------------
		glfwSwapBuffers(window);
		glfwPollEvents();
	}

	skybox.Terminate();

	glfwTerminate();
	return 0;
}

// process all input: query GLFW whether relevant keys are pressed/released this frame and react accordingly
// ---------------------------------------------------------------------------------------------------------
void my_input(GLFWwindow *window, int key, int scancode, int action, int mode)
{
	if (glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS)
		glfwSetWindowShouldClose(window, true);
	if (reco == false) {
		if (glfwGetKey(window, GLFW_KEY_W) == GLFW_PRESS)
			camera.ProcessKeyboard(FORWARD, (float)deltaTime);
		if (glfwGetKey(window, GLFW_KEY_S) == GLFW_PRESS)
			camera.ProcessKeyboard(BACKWARD, (float)deltaTime);
		if (glfwGetKey(window, GLFW_KEY_A) == GLFW_PRESS)
			camera.ProcessKeyboard(LEFT, (float)deltaTime);
		if (glfwGetKey(window, GLFW_KEY_D) == GLFW_PRESS)
			camera.ProcessKeyboard(RIGHT, (float)deltaTime);
	}
	//To Configure Model
	if (glfwGetKey(window, GLFW_KEY_Y) == GLFW_PRESS)
		posZ++;
	if (glfwGetKey(window, GLFW_KEY_H) == GLFW_PRESS)
		posZ--;
	if (glfwGetKey(window, GLFW_KEY_G) == GLFW_PRESS)
		posX--;
	if (glfwGetKey(window, GLFW_KEY_J) == GLFW_PRESS)
		posX++;
	if (glfwGetKey(window, GLFW_KEY_X) == GLFW_PRESS)
		rotRodIzq--;
	if (glfwGetKey(window, GLFW_KEY_C) == GLFW_PRESS)
		rotRodIzq++;
	if (glfwGetKey(window, GLFW_KEY_V) == GLFW_PRESS)
		giroMonito--;
	if (glfwGetKey(window, GLFW_KEY_B) == GLFW_PRESS)
		giroMonito++;
	/*if (glfwGetKey(window, GLFW_KEY_RIGHT) == GLFW_PRESS) {
		skateX++;
	}
	if (glfwGetKey(window, GLFW_KEY_LEFT) == GLFW_PRESS) {
		skateX--;
	}*/
	//boton coche animacion
	if (glfwGetKey(window, GLFW_KEY_R) == GLFW_PRESS && permisoIda) {
		cocheIda = true;
		permisoIda = false;
	}
	if (glfwGetKey(window, GLFW_KEY_R) == GLFW_PRESS && permisoRegreso) {
		cocheRegreso = true;
		permisoRegreso = false;
	}

	//boton animacion tele
	if (glfwGetKey(window, GLFW_KEY_T) == GLFW_PRESS && animTele == false) {
		animTele = true;
	}
	/*if (glfwGetKey(window, GLFW_KEY_E) == GLFW_PRESS) {
		ringPhone = true;
		ringIda = true;
	}
	if (glfwGetKey(window, GLFW_KEY_E) == GLFW_PRESS && ringPhone == true) {
		ringPhone = false;
	}*/

	//Car animation
	if (key == GLFW_KEY_SPACE && action == GLFW_PRESS)
		animacion ^= true;

	//To play KeyFrame animation 
	//To play KeyFrame animation 
	if (key == GLFW_KEY_P && action == GLFW_PRESS)
	{
		if (play == false && (FrameIndex > 1))
		{
			std::cout << "Play animation" << std::endl;
			resetElements();
			//First Interpolation				
			interpolation();

			play = true;
			playIndex = 0;
			i_curr_steps = 0;
		}
		else
		{
			play = false;
			std::cout << "Not enough Key Frames" << std::endl;
		}
	}

	/*To Save a KeyFrame
	if (key == GLFW_KEY_L && action == GLFW_PRESS)
	{
		if (FrameIndex < MAX_FRAMES)
		{
			saveFrame();
		}
	}*/

	if (glfwGetKey(window, GLFW_KEY_N) == GLFW_PRESS) {
		if (tiempo == 0) {
			tiempo = 1;


		}
		else {
			tiempo = 0;
		}
	}
	if (glfwGetKey(window, GLFW_KEY_E) == GLFW_PRESS) {
		reco = true;
		reco1 = true;
		xAvance = 0;
		yAvance = 0;
		zAvance = 0;

	}
}
// glfw: whenever the window size changed (by OS or user resize) this callback function executes
// ---------------------------------------------------------------------------------------------
void framebuffer_size_callback(GLFWwindow* window, int width, int height)
{
	// make sure the viewport matches the new window dimensions; note that width and 
	// height will be significantly larger than specified on retina displays.
	glViewport(0, 0, width, height);
}

// glfw: whenever the mouse moves, this callback is called
// -------------------------------------------------------
void mouse_callback(GLFWwindow* window, double xpos, double ypos)
{
	if (firstMouse)
	{
		lastX = xpos;
		lastY = ypos;
		firstMouse = false;
	}

	float xoffset = xpos - lastX;
	float yoffset = lastY - ypos; // reversed since y-coordinates go from bottom to top

	lastX = xpos;
	lastY = ypos;

	camera.ProcessMouseMovement(xoffset, yoffset);
}
// glfw: whenever the mouse scroll wheel scrolls, this callback is called
// ----------------------------------------------------------------------
void scroll_callback(GLFWwindow* window, double xoffset, double yoffset)
{
	camera.ProcessMouseScroll(yoffset);
}