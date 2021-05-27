#define _CRT_SECURE_NO_WARNINGS		// ???

#include <iostream>
#include <sstream>
#include <string>
#include <memory>
#include <fstream>
#include <thread>

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

void t_generate(std::vector<TestGen*>& test_gens, int& labs_num, int i) {
	//test_gens[i]->Generate();
	std::cout << "NAME    [" << i << "]: " << test_gens[i]->name << std::endl;
	std::cout << "GROUP   [" << i << "]: " << test_gens[i]->group << std::endl;
	std::cout << "LAB NUM [" << i << "]: " << test_gens[i]->lab_num << std::endl;
	std::cout << "LAB VAR [" << i << "]: " << test_gens[i]->lab_var << std::endl;
	std::cout << "******************************" << std::endl;
	int j = 1000;
	while (j > 0) {
		std::cout << i << std::endl;
		j--;
	}
	test_gens[i]->status = (char*)"DONE";
	// ???
	//test_gens.erase(test_gens.begin() + i);
	//labs_num--;
}

void ShowWindow(bool* p_open, std::vector<TestGen*>& test_gens, std::vector<std::thread>& threads) {
	//static char buf1[64] = ""; ImGui::InputText("default", buf1, 64);
	static char buf[64] = "";
	ImGui::InputText("Enter how many labs you want to test", buf, 64, ImGuiInputTextFlags_CharsDecimal);
	ImGui::SameLine();

	static int labs_num;
	static bool button_enter = false;
	if (ImGui::Button("ENTER")) {
		if (!test_gens.empty()) {
			test_gens.clear();
		}
		labs_num = atoi(buf);
		for (int i = 0; i < labs_num; i++) {
			test_gens.push_back(new TestGen(1));
		}
		button_enter = true;
	}
	if (button_enter){
		ImGui::Text("Enter parameters for every student");
		// Group NameSurname LabNum Var Button
		ImGui::Columns(7, "columns");
		ImGui::Separator();
		ImGui::Text("#"); ImGui::NextColumn();
		ImGui::Text("Group"); ImGui::NextColumn();
		ImGui::Text("Name, surname"); ImGui::NextColumn();
		ImGui::Text("Lab number"); ImGui::NextColumn();
		ImGui::Text("Task number"); ImGui::NextColumn();
		ImGui::Text("Button"); ImGui::NextColumn();
		ImGui::Text("Status"); ImGui::NextColumn();
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

		/*const char* names[3] = { "One", "Two", "Three" };
		const char* paths[3] = { "/path/one", "/path/two", "/path/three" };
		static int selected = -1;*/

		/*static int labs_num = atoi(buf);
		for (int i = 0; i < labs_num; i++) {
			test_gens.push_back(new TestGen(1));
		}*/


//#define NAME_ENTER(index) name_enter##index
//#define GROUP_ENTER(index) group_enter##index

		for (int i = 0; i < labs_num; i++)
		{
			//char* NAME_ENTER(i) = "";

			//std::cout << NAME_ENTER(i);
			/*char label[32];
			sprintf(label, "%04d", i);
			if (ImGui::Selectable(label, selected == i, ImGuiSelectableFlags_SpanAllColumns))
				selected = i;*/
			char label[64];
			sprintf(label, "%d", i+1);
			ImGui::Text(label); 
			ImGui::NextColumn();

			//sprintf(label, "group %d", i+1);
			//static char group_enter[64] = ""; 
			//ImGui::InputText(label, group_enter, 64);
			//ImGui::NextColumn();

			sprintf(label, "group %d", i + 1);
			ImGui::InputText(label, test_gens[i]->group, 64);
			ImGui::NextColumn();
			
			sprintf(label, "name %d", i+1);
			ImGui::InputText(label, test_gens[i]->name, 64);
			ImGui::NextColumn();
			
			sprintf(label, "lab num %d", i + 1);
			//static int item_current = 0;		// index of current item
			const char* items_lab_num[] = { "1", "2", "3", "4", "5", "6" };
			ImGui::Combo(label, &test_gens[i]->item_current_lab, items_lab_num, IM_ARRAYSIZE(items_lab_num));
			test_gens[i]->lab_num = atoi(items_lab_num[test_gens[i]->item_current_lab]);
			ImGui::NextColumn();
			//std::cout << atoi(items_lab_num[test_gens[i]->item_current_lab]);
			//std::cout << test_gens[i]->lab_num;
			
			const char* items_lab_var[] = { "1", "2", "3", "4", "5", "6", "7", "8", "9", "10" };
			sprintf(label, "task num %d", i + 1);
			//static int item_current1 = 0;
			ImGui::Combo(label, &test_gens[i]->item_current_var, items_lab_var, IM_ARRAYSIZE(items_lab_var));
			test_gens[i]->lab_var = atoi(items_lab_var[test_gens[i]->item_current_var]);
			ImGui::NextColumn();

			static bool status_column = false;
			sprintf(label, "GENERATE %d", i + 1);
			if (ImGui::Button(label)){
				////test_gens[i]->Generate();
				//std::cout << "NAME    [" << i << "]: " << test_gens[i]->name << std::endl;
				//std::cout << "GROUP   [" << i << "]: " << test_gens[i]->group << std::endl;
				//std::cout << "LAB NUM [" << i << "]: " << test_gens[i]->lab_num << std::endl;
				//std::cout << "LAB VAR [" << i << "]: " << test_gens[i]->lab_var << std::endl;
				//std::cout << "******************************" << std::endl;
				//// ???
				//test_gens.erase(test_gens.begin() + i);
				//labs_num--;

#define THREAD(index) t ## index		// ???
				/*std::thread THREAD(i)(t_generate, std::ref(test_gens), std::ref(labs_num), i);
				threads.push_back(THREAD(i));*/
				//std::thread THREAD(i)(t_generate, std::ref(test_gens), std::ref(labs_num), i);
				threads.push_back(std::thread (t_generate, std::ref(test_gens), std::ref(labs_num), i));


			}
			// TODO: maybe do this as a table, not columns
			ImGui::NextColumn();
			ImGui::Text(test_gens[i]->status);

			ImGui::NextColumn();

		}
		ImGui::Columns(1);
		ImGui::Separator();


		if (ImGui::Button("GENERATE ALL")) {
			//std::cout << test_gens.size();
			for (int i = 0; i < labs_num; i++) {
				//test_gens[i]->Generate();
				std::cout << "NAME    [" << i << "]: " << test_gens[i]->name << std::endl;
				std::cout << "GROUP   [" << i << "]: " << test_gens[i]->group << std::endl;
				std::cout << "LAB NUM [" << i << "]: " << test_gens[i]->lab_num << std::endl;
				std::cout << "LAB VAR [" << i << "]: " << test_gens[i]->lab_var << std::endl;
				std::cout << "******************************" << std::endl;
			}
		}
		ImGui::SameLine();
		ImGui::Text("Press this button to generate all tests at once.");

	}
}

int main(int argc, char** argv) {

	std::vector<TestGen*> test_gens;
	std::vector<std::thread> threads;

	// Probably make GLFW thing as a separate function
	// GLFW below

	GLFWwindow* window;

	/* Initialize the library */
	if (!glfwInit())
		return -1;


	/* Create a windowed mode window and its OpenGL context */
	window = glfwCreateWindow(1920, 1080, "Labs Testing", NULL, NULL);
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
			ShowWindow(&show_window, test_gens, threads);
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

	for (auto& th : threads) th.join();
	/*for (int i = 0; i < threads.size(); i++) {
		threads[i].join();
	}*/

	//THREAD(t_index).join();	// ???

	// *******************************
	//tg->Generate();
	//std::cout << "DONE";
	// *******************************

	//getchar();
	return 0;
}