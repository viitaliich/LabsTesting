#define _CRT_SECURE_NO_WARNINGS		// ???


#include <iostream>
#include <sstream>
#include <string>
#include <memory>
#include <fstream>

#include <GL/glew.h>		// maybe we don't need this include here, because we don't draw anything ???
#include <GLFW/glfw3.h>		// must be included after <GL/glew.h>

#include "imgui/imgui.h"
//#include "imgui/imgui_impl_glfw_gl3.h"
#include "imgui/imgui_impl_glfw.h"
#include "imgui/imgui_impl_opengl3.h"
//#include "imgui/imgui_demo.cpp"

#include "common.h"
#include "TestGen.h"

// declarations
std::string run_program(std::string& path);
void modify_input_code();

// definitions

std::string run_program(std::string& path) {
	
	check_file(path);

	// TODO: it can be replaced with identification by thread number (thread ID)

	size_t index = path.length()-1;
	while (path[index] != '.' && index > 0) {
		index--;
	}
	size_t name_end = index - 1;

	while (path[index] != '\\' && index > 0) {
		index--;
	}
	size_t name_start = index + 1;

	size_t length = 0;
	if (name_end != 0 && name_start != 0 && name_end != name_start)
		length = name_end - name_start + 1;
	else {
		std::cout << "ERROR: file path is wrong\n";
		exit(1);
	}
	std::string file_name = path.substr(name_start, length);	// +".txt";
	
	std::stringstream ss;
	ss << path << " > " << file_name;
	std::string cmd(ss.str());
	ss << system(cmd.c_str());

	std::ifstream res_file;
	res_file.open(file_name);
	if (res_file.is_open()) {
		std::string res;
		getline(res_file, res);
		res_file.close();
		return res;
	}
	else {
		std::cout << "ERROR: file [" << file_name << "] is not opened\n";
		exit(1);
	}
}

void modify_input_code(std::string& data, const std::string& path) {
	check_file(path);

	std::ofstream file(path);
	file << data;
	file.close();
}

void ShowWindow(bool* p_open) {
	//static char buf1[64] = ""; ImGui::InputText("default", buf1, 64);
	static char buf[64] = "";	// TODO: optimize 64 ???
	ImGui::InputText("Enter how many labs you want to test", buf, 64, ImGuiInputTextFlags_CharsDecimal);
	ImGui::SameLine();

	static bool button_enter = false;
	if (ImGui::Button("ENTER")) button_enter = true;

	if (button_enter){
		ImGui::Text("Enter parameters for every student");
		// Group NameSurname LabNum Var Button
		ImGui::Columns(5, "columns");
		ImGui::Separator();
		ImGui::Text("Group"); ImGui::NextColumn();
		ImGui::Text("Name, surname"); ImGui::NextColumn();
		ImGui::Text("Lab number"); ImGui::NextColumn();
		ImGui::Text("Task number"); ImGui::NextColumn();
		ImGui::Text("Button"); ImGui::NextColumn();
		ImGui::Separator();
		
		/*const char* names[3] = { "One", "Two", "Three" };
		const char* paths[3] = { "/path/one", "/path/two", "/path/three" };
		static int selected = -1;
		for (int i = 0; i < 3; i++)
		{
			char label[32];
			sprintf(label, "%04d", i);
			if (ImGui::Selectable(label, selected == i, ImGuiSelectableFlags_SpanAllColumns))
				selected = i;
			bool hovered = ImGui::IsItemHovered();
			ImGui::NextColumn();
			ImGui::Text(names[i]); ImGui::NextColumn();
			ImGui::Text(paths[i]); ImGui::NextColumn();
			ImGui::Text("%d", hovered); ImGui::NextColumn();
		}*/

		const char* names[3] = { "One", "Two", "Three" };
		const char* paths[3] = { "/path/one", "/path/two", "/path/three" };
		static int selected = -1;
		for (int i = 0; i < /*atoi(buf)*/ 3; i++)
		{
			//char label[32];
			//sprintf(label, "%04d", i);
			//if (ImGui::Selectable(label, selected == i, ImGuiSelectableFlags_SpanAllColumns))
			//	selected = i;
			
			static char group_enter[64] = ""; ImGui::InputText("", group_enter, 64);
			ImGui::NextColumn();
			
			static char name_enter[64] = ""; ImGui::InputText("", name_enter, 64);
			ImGui::NextColumn();
			
			const char* lab_numbers[] = { "1", "2", "3", "4", "5", "6" };
			static int item_current = 0;
			ImGui::Combo("", &item_current, lab_numbers, IM_ARRAYSIZE(lab_numbers));
			ImGui::NextColumn();
			
			const char* variants[] = { "1", "2", "3", "4", "5", "6", "7", "8", "9", "10" };
			//static int item_current = 0;
			ImGui::Combo("", &item_current, variants, IM_ARRAYSIZE(variants));
			ImGui::NextColumn();

			ImGui::Button("GENERATE");
			ImGui::NextColumn();
		}
		ImGui::Columns(1);
		ImGui::Separator();
	}
}

int main(int argc, char** argv) {
	
	// Probably make GLFW thing as a separate function
	// GLFW below

	GLFWwindow* window;

	/* Initialize the library */
	if (!glfwInit())
		return -1;


	/* Create a windowed mode window and its OpenGL context */
	window = glfwCreateWindow(640, 480, "Hello World", NULL, NULL);
	if (!window)
	{
		glfwTerminate();
		return -1;
	}

	/* Make the window's context current */
	glfwMakeContextCurrent(window);

	// Must be after setting of valid context
	// maybe we don't need this here, because we don't use OpenGL functions ???
	if (glewInit() != GLEW_OK)
		std::cout << "ERROR: not GLEW_OK\n";

	ImGui::CreateContext();
	//ImGui_ImplGlfwGL3_Init(window, true);
	//ImGui_ImplGlfw_InitForOpenGL(window, true);
	ImGui_ImplOpenGL3_Init();
	ImGui_ImplGlfw_InitForOpenGL(window, true);

	// Setup style
	ImGui::StyleColorsDark();
	//ImGui::StyleColorsClassic();

	// Variables for ImGui num.1 example
	bool show_demo_window = true;		// default Checkbox value
	bool show_another_window = false;	// default Checkbox value
	//ImVec4 clear_color = ImVec4(0.45f, 0.55f, 0.60f, 1.00f);
	ImVec4 clear_color = ImVec4(0.45f, 0.55f, 0.60f, 1.00f);

	bool show_window = true;		// default Checkbox value

	/* Loop until the user closes the window */
	while (!glfwWindowShouldClose(window))
	{
		//ImGui_ImplGlfwGL3_NewFrame();	
		ImGui_ImplOpenGL3_NewFrame();	
		ImGui_ImplGlfw_NewFrame();	
		ImGui::NewFrame();

		/* Render here */
		glClear(GL_COLOR_BUFFER_BIT);		// maybe rid of this

		// 1. Show a simple window.
		//{
		//	static float f = 0.0f;
		//	static int counter = 0;
		//	//ImGui::Text("Hello, world!");                           // Display some text (you can use a format string too)
		//	ImGui::SliderFloat("float", &f, 0.0f, 1.0f);            // Edit 1 float using a slider from 0.0f to 1.0f    
		//	ImGui::ColorEdit3("clear color", (float*)&clear_color); // Edit 3 floats representing a color

		//	ImGui::Checkbox("Demo Window", &show_demo_window);      // Edit bools storing our windows open/close state
		//	ImGui::Checkbox("Another Window", &show_another_window);

		//	if (ImGui::Button("Button"))                            // Buttons return true when clicked (NB: most widgets return true when edited/activated)
		//		counter++;
		//	ImGui::SameLine();
		//	ImGui::Text("counter = %d", counter);

		//	ImGui::Text("Application average %.3f ms/frame (%.1f FPS)", 1000.0f / ImGui::GetIO().Framerate, ImGui::GetIO().Framerate);
		//}
		//// 2. Show another simple window. In most cases you will use an explicit Begin/End pair to name your windows.
		//if (show_another_window)
		//{
		//	ImGui::Begin("Another Window", &show_another_window);		// ???
		//	ImGui::Text("Hello from another window!");
		//	if (ImGui::Button("Close Me"))
		//		show_another_window = false;
		//	ImGui::End();
		//}

		// 3. Show the ImGui demo window. Most of the sample code is in ImGui::ShowDemoWindow(). Read its code to learn more about Dear ImGui!
		if (show_demo_window)
		{
			//ImGui::SetNextWindowPos(ImVec2(650, 20), ImGuiCond_FirstUseEver); // Normally user code doesn't need/want to call this because positions are saved in .ini file anyway. Here we just want to make the demo initial state a bit more friendly!
			ImGui::ShowDemoWindow(&show_demo_window);
		}

		if (show_window) {
			ShowWindow(&show_window);
		}

		ImGui::Render();
		//ImGui_ImplGlfwGL3_RenderDrawData(ImGui::GetDrawData());
		ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());

		/* Swap front and back buffers */
		glfwSwapBuffers(window);

		/* Poll for and process events */
		glfwPollEvents();
	}

	// Cleanup
	//ImGui_ImplGlfwGL3_Shutdown();
	ImGui_ImplGlfw_Shutdown();
	ImGui_ImplOpenGL3_Shutdown();
	ImGui::DestroyContext();

	glfwTerminate();


	// *******************************
	TestGen* tg = new TestGen(1);
	tg->Generate();
	std::cout << "DONE";
	// *******************************

	//getchar();
	return 0;
}