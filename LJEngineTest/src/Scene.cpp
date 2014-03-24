#include "Scene.h"

void SceneInit(LJApplication& app)
{
	// Texture Projection
/*	LJ1stPerCtrller cam;
	cam.SetPos(LJVector3(0.f, 0.f, 10.f));
	LJMatrix4 camView = BuildViewMatrix(cam.GetRight(), cam.GetUp(), cam.GetDir(), cam.GetPos());
	LJMatrix4 camProj, camOrth;
	BuildPersMatrix(30.f, 1.f, 0.01f, 1000.f, camProj, camOrth);
	LJMatrix4 camScale(0.5f, 0.f, 0.f, 0.f,
			           0.0f, 0.5f,0.f, 0.f,
			           0.0f, 0.0f,0.5f,0.f,
			           0.5f, 0.5f,0.5f,1.f);
	LJMatrix4 camSPV = camScale * camProj * camView;
	LJMaterial *pMat3 = g_pMatManager->GetMaterial(nMat3);
	pMat3->SetParam("ProjectorMatrix", LJMATRIX4f, camSPV);
	LJTexture *pTex3 = pMat3->GetTexture("projectMap");
	if(!pTex3) throw "Texture set fialed";
	pTex3->SetParameter(LJ_TEXTURE_WRAP_S, LJ_CLAMP_TO_BORDER);
	pTex3->SetParameter(LJ_TEXTURE_WRAP_T, LJ_CLAMP_TO_BORDER);
*/

}
