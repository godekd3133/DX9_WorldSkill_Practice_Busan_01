#pragma once
#include <iostream>
#include <string>
#include <list>
#include <vector>
#include <map>
#include <functional>
#include <queue>
#include <fstream>
#include <algorithm>
#include <functional>
#include <set>
#include <thread>
#include <future>
#include <mutex>

using namespace std;

const INT WINSIZEX = 1920;
const INT WINSIZEY = 1080;
const bool WINDOWED = true;

#define g_Device DXUTGetD3D9Device()
#define dt DXUTGetElapsedTime() * INPUT.TimeScale
#define udt  DXUTGetElapsedTime()
#define SCREEN_CENTER Vector2(WINSIZEX/2.F, WINSIZEY/2.f)
#define VEC3_UP Vector3(0,1,0)
#define VEC3_DOWN Vector3(0,-1,0)
#define VEC3_LEFT Vector3(-1,0,0)
#define VEC3_RIGHT Vector3(1,0,0)
#define VEC3_FRONT Vector3(0,0,1)
#define VEC3_BACK Vector3(0,0,-1)

#define VEC2_UP Vector2(0,-1)
#define VEC2_DOWN Vector2(0,1)
#define VEC2_LEFT Vector2(-1,0)
#define VEC2_RIGHT Vector2(1,0)



using Vector2 = D3DXVECTOR2;
using Vector3 = D3DXVECTOR3;
using Vector4 = D3DXVECTOR4;
using Color = D3DXCOLOR;
using Matrix = D3DXMATRIX;
using Quaternion = D3DXQUATERNION;
using Event = std::function<void()>;
template<typename T>
T Lerp(T start, T end, float t)
{
	return start + t * (end - start);
}
namespace my
{
	static Vector3 GetDirection(Vector3 _vStart, Vector3 _vEnd)
	{
		Vector3 vDir = _vEnd - _vStart;
		D3DXVec3Normalize(&vDir, &vDir);

		return vDir;
	}
	static Vector3 GetRotatedDir(Vector2 _vDir, float _fRot)
	{
		Vector2 vDir = _vDir;

		Matrix matRot;
		D3DXMatrixRotationZ(&matRot, D3DXToRadian(_fRot));

		D3DXVec2TransformNormal(&vDir, &vDir, &matRot);

		return Vector3(vDir.x, 0.f, vDir.y);
	}
	static Vector3 GetRotatedDir(Vector3 _vDir, float _fRot)
	{
		Vector3 vDir = _vDir;

		Matrix matRot;
		D3DXMatrixRotationY(&matRot, D3DXToRadian(_fRot));

		D3DXVec3TransformNormal(&vDir, &vDir, &matRot);

		return Vector3(vDir.x, 0.f, vDir.z);
	}
	static float GetDirAngle(Vector2 _vDir)
	{
		float angle = atan2f(_vDir.y, _vDir.x);

		return D3DXToDegree(angle);
	}
	static Vector3 GetDirectionFromQuaternion(Quaternion _Quat)
	{
		Matrix matRot;
		D3DXMatrixRotationQuaternion(&matRot, &_Quat);

		Vector3 vRot = Vector3(0, 0, 1);
		D3DXVec3TransformNormal(&vRot, &vRot, &matRot);
		return vRot;
	}
	static float GetDirAngle(Vector3 _vDir)
	{
		float angle = atan2f(_vDir.x, _vDir.z);

		return D3DXToDegree(angle);
	}
	static int RandRange(int _Min, int _Max)
	{
		int num = rand() % (int)((_Max - _Min)) + (int)(_Min);
		return num;
	}

	static float GetLength(Vector2 _v1, Vector2 _v2)
	{
		float length = D3DXVec2Length(&(_v2 - _v1));
		return length;
	}

	static float GetLength(Vector3 _v1, Vector3 _v2)
	{
		float length = D3DXVec3Length(&(_v2 - _v1));
		return length;
	}

	static Quaternion QuatEular(Vector3 _vRot)
	{
		Quaternion Quat;
		D3DXQuaternionRotationYawPitchRoll(&Quat, D3DXToRadian(_vRot.y), D3DXToRadian(_vRot.x), D3DXToRadian(_vRot.z));
		return Quat;
	}
};
using namespace my;
enum class RenderMode {RM_Default , RM_UI, RM_Billboard, RM_BillboardNonUI};
enum class SortingLayer { SR_Default,SR_Effect, SR_UI,SR_UI2,SR_SCREEEN};

enum class  Tag{Untagged,Map,Player,Enemy,Item,UI};
#include "DXUT/Optional/SDKsound.h"
#include "DXUT/Optional/SDKwavefile.h"
#pragma comment(lib, "dsound.lib")

#include "CScheduleAdmin.h"
#include "CSprite.h"
#include "CScene.h"
#include "MeshLoader.h"

#include "CComponent.h"
#include "CGameObject.h"
#include "CTransform.h"
#include "CRenderer2D.h"
#include "CRenderer3D.h"
#include "CSpriteRenderer.h"
#include "CMeshRenderer.h"
#include "CEffect.h"
#include "CText.h"

#include "CStageMap.h"
#include "CRigidBody.h"
#include "CAnimation2D.h"
#include "CAnimation3D.h"
#include "CAnimator3D.h"
#include "CAnimator2D.h"
#include "CCollider.h"
#include "CPlayerMovement.h"
#include "CDamageFont.h"
#include "CPlayerBullet.h"
#include "CEnemy.h"
#include "CEnemy01.h"
#include "CEnemy02.h"
#include "CEnemy03.h"

 
#include "CButton.h"
#include "CPlayerUI.h"
#include "CItem.h"

#include "CSingleton.h"

#include "CGraphicsManager.h"
#include "CCameraManager.h"
#include "CInputManager.h"
#include "CSceneManager.h"
#include "CObjectManager.h"
#include "CGameManager.h"