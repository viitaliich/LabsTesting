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
#include "imgui/ImGuiFileBrowser.h"


#include "common.h"
#include "TestGen.h"

// declarations

void t_generate(std::vector<TestGen*>& test_gens, int& labs_num, int i) {
	test_gens[i]->status = (char*)"IN PROGRESS ...";
	test_gens[i]->Generate();
	std::cout << "NAME    [" << i << "]: " << test_gens[i]->name << std::endl;
	std::cout << "GROUP   [" << i << "]: " << test_gens[i]->group << std::endl;
	std::cout << "LAB NUM [" << i << "]: " << test_gens[i]->lab_num << std::endl;
	std::cout << "LAB VAR [" << i << "]: " << test_gens[i]->lab_var << std::endl;
	std::cout << "source [" << i << "]: " << test_gens[i]->path_source << std::endl;
	std::cout << "******************************" << std::endl;
	int j = 1000;
	while (j > 0) {
		//std::cout << i << std::endl;
		j--;
	}
	test_gens[i]->status = (char*)"DONE";
}

void ShowWindow(bool* p_open, std::vector<TestGen*>& test_gens, std::vector<std::thread>& threads) {

	static imgui_addons::ImGuiFileBrowser file_dialog;

	//static char buf1[64] = ""; ImGui::InputText("default", buf1, 64);
	static char buf[64] = "";
	ImGui::InputText("Enter how many labs you want to test", buf, 64, ImGuiInputTextFlags_CharsDecimal);
	ImGui::SameLine();

	static int labs_num;
	static bool button_enter = false;
	if (ImGui::Button("ENTER lab num")) {
		if (!test_gens.empty()) {
			test_gens.clear();
		}
		labs_num = atoi(buf);
		for (int i = 0; i < labs_num; i++) {
			test_gens.push_back(new TestGen());
		}
		button_enter = true;
	}

	if (button_enter){
		static char buffer[64] = "";
		ImGui::InputText("Enter MAX points per lab", buffer, 64, ImGuiInputTextFlags_CharsDecimal);
		ImGui::SameLine();
		if (ImGui::Button("ENTER mark")) {
			for (int i = 0; i < labs_num; i++) {
				test_gens[i]->max_mark = atoi(buffer);
			}
		}

		ImGui::Text("Enter parameters for every student");
		// Group NameSurname LabNum Var Button
		ImGui::Columns(12, "columns");
		ImGui::Separator();
		ImGui::Text("#"); ImGui::NextColumn();
		ImGui::Text("Group"); ImGui::NextColumn();
		ImGui::Text("Name\nSurname"); ImGui::NextColumn();
		ImGui::Text("Lab number"); ImGui::NextColumn();
		ImGui::Text("Task number"); ImGui::NextColumn();
		ImGui::Text("Compiler\nexecutable file"); ImGui::NextColumn();
		ImGui::Text("Path"); ImGui::NextColumn();
		ImGui::Text("Input\nsource code"); ImGui::NextColumn();
		ImGui::Text("Path"); ImGui::NextColumn();
		ImGui::Text("Generate"); ImGui::NextColumn();
		ImGui::Text("Status"); ImGui::NextColumn();
		ImGui::Text("Mark"); ImGui::NextColumn();
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

			// COMPILER...
			
			static char lbl_compiler[64];		// label
			static int index_compiler;			// index for differences
			sprintf(label, "COMPILER\nEXECUTABLE FILE %d", i + 1);
			if (ImGui::Button(label)) {
				index_compiler = i;
				sprintf(lbl_compiler, "Choose compiler executable file %d", index_compiler + 1);
				ImGui::OpenPopup(lbl_compiler);
			}
			if (file_dialog.showFileDialog(lbl_compiler, imgui_addons::ImGuiFileBrowser::DialogMode::OPEN, ImVec2(600, 300), "*.*")) {
				sprintf(test_gens[index_compiler]->path_compiler, (char*)file_dialog.selected_path.c_str());
			}

			ImGui::NextColumn();

			ImGui::Text(test_gens[i]->path_compiler);
			ImGui::NextColumn();

			static char lbl[64];		// label
			static int index;			// index for differences
			sprintf(label, "INPUT\nSOURCE CODE %d", i + 1);
			if (ImGui::Button(label)) {
				index = i;
				sprintf(lbl, "Choose input source file %d", index + 1);
				ImGui::OpenPopup(lbl);
			}
			if(file_dialog.showFileDialog(lbl, imgui_addons::ImGuiFileBrowser::DialogMode::OPEN, ImVec2(600, 300), "*.*")){
				sprintf(test_gens[index]->path_source, (char*)file_dialog.selected_path.c_str());
			}
			ImGui::NextColumn();

			ImGui::Text(test_gens[i]->path_source);
			ImGui::NextColumn();

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
				
//#define THREAD(index) t ## index		// ???
				/*std::thread THREAD(i)(t_generate, std::ref(test_gens), std::ref(labs_num), i);
				threads.push_back(THREAD(i));*/
				//std::thread THREAD(i)(t_generate, std::ref(test_gens), std::ref(labs_num), i);
				threads.push_back(std::thread (t_generate, std::ref(test_gens), std::ref(labs_num), i)); 


			}
			// TODO: maybe do this as a table, not columns
			ImGui::NextColumn();
			ImGui::Text(test_gens[i]->status);

			char buf[64];
			sprintf(buf, "%f", test_gens[i]->mark);
			ImGui::NextColumn();
			ImGui::Text(buf);

			ImGui::NextColumn();

		}
		ImGui::Columns(1);
		ImGui::Separator();


		if (ImGui::Button("GENERATE ALL")) {
			//std::cout << test_gens.size();
			for (int i = 0; i < labs_num; i++) {
				threads.push_back(std::thread(t_generate, std::ref(test_gens), std::ref(labs_num), i));
				//test_gens[i]->Generate();
				//std::cout << "NAME    [" << i << "]: " << test_gens[i]->name << std::endl;
				//std::cout << "GROUP   [" << i << "]: " << test_gens[i]->group << std::endl;
				//std::cout << "LAB NUM [" << i << "]: " << test_gens[i]->lab_num << std::endl;
				//std::cout << "LAB VAR [" << i << "]: " << test_gens[i]->lab_var << std::endl;
				//std::cout << "******************************" << std::endl;
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