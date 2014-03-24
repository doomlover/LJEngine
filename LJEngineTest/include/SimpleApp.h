/*
 * SimpleApp.h
 *
 *  Created on: Mar 24, 2014
 *      Author: liu
 */

#ifndef SIMPLEAPP_H_
#define SIMPLEAPP_H_

#include <GLFW/glfw3.h>

#include "LJApplication.h"
#include "LJGeneralType.h"
#include "LJTextureManager.h"
#include "LJMaterialManager.h"
#include "LJRenderManager.h"
#include "LJMesh.h"
#include "LJMaterial.h"
#include "LJTechnique.h"
#include "LJPass.h"
#include "Utils.h"
#include "LJ1stPerCtrller.h"
#include "LJShader.h"
#include "LJRenderState.h"
#include "LJGeometry.h"
#include "LJRenderPass.h"
#include "GLFWFrameListener.h"
#include "GLFWTimer.h"
#include "LJCameraTools.h"
#include "LJEffectFileParser.h"
#include "LJRenderTexture.h"


class SimpleApp : public LJApplication
{
private:
	UINT nMainSceneTex;
	vector<LJMesh*> pMeshes;
	GLFWwindow *glfwWindow;
	double w2, h2;
	LJ1stPerCtrller *m_Camera;
	LJNode *m_MainSceneNode;
	LJNode *m_WindowSceneNode;

private:
	void SimpleInit();
	void SimpleCleanUp();
	void AppCreateWindow();
	void SetBasicScene();
	void SetWindowScene();
public:
	SimpleApp();
	~SimpleApp(void);

	class SimpleFrameListener;
	friend class SimpleFrameListener;
	class SimpleFrameListener : public LJFrameListener
	{
		void WindwoFocusCB(GLFWwindow *window, int hasFocus);
		friend void GLFWKeyCB(GLFWwindow* window, int key, int scancode, int action, int mods);
		SimpleApp *app;
	public:
		SimpleFrameListener(SimpleApp *app);
		~SimpleFrameListener(void){};
		void FrameStarted(float tpf, LJApplication *app);
		void FrameEnded(float tpf, LJApplication *app);
		void UpdateCamera(float tpf, LJApplication *app);
	};
};


#endif /* SIMPLEAPP_H_ */
