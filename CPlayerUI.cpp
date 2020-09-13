#include "DXUT.h"
#include "CPlayerUI.h"


CPlayerUI::CPlayerUI()
{
	m_Color = Color(1, 1, 1, 1);
	m_SortingLayer = SortingLayer::SR_UI2;
}


CPlayerUI::~CPlayerUI()
{
}

void CPlayerUI::Awake()
{
	CGameObject * PlayerStatusBG01 = OBJ.Create("UI", Tag::UI);
	PlayerStatusBG01->ac<CSpriteRenderer>()->Init(SPRITE("UI_PLAYERSTATUS_01"), SortingLayer::SR_UI, RenderMode::RM_UI);
	PlayerStatusBG01->gc<CSpriteRenderer>()->m_vAnchor = Vector2(0, 0);
	PlayerStatusBG01->tf->m_vPos = Vector3(50, 0, 0);

	CGameObject * PlayerStatusBG03 = OBJ.Create("UI", Tag::UI);
	PlayerStatusBG03->ac<CSpriteRenderer>()->Init(SPRITE("UI_PLAYERSTATUS_03"), SortingLayer::SR_UI, RenderMode::RM_UI);
	PlayerStatusBG03->gc<CSpriteRenderer>()->m_vAnchor = Vector2(0, 0);
	PlayerStatusBG03->tf->m_vPos = Vector3(50, 0, 0);

	m_pHpBar_Bg = OBJ.Create("UI", Tag::UI);
	m_pHpBar_Bg->ac<CSpriteRenderer>()->Init(SPRITE("UI_PLAYERSTATUS_HPBAR_BG"), SortingLayer::SR_UI, RenderMode::RM_UI);
	m_pHpBar_Bg->tf->m_vPos = Vector3(450, 120, 0);

	m_pHpBar_Yellow = OBJ.Create("UI", Tag::UI);
	m_pHpBar_Yellow->ac<CSpriteRenderer>()->Init(SPRITE("UI_PLAYERSTATUS_HPBAR_YELLOW"), SortingLayer::SR_UI, RenderMode::RM_UI);
	m_pHpBar_Yellow->tf->m_vPos = Vector3(450, 120, 0);

	m_pHpBar = OBJ.Create("UI", Tag::UI);
	m_pHpBar->ac<CSpriteRenderer>()->Init(SPRITE("UI_PLAYERSTATUS_HPBAR"), SortingLayer::SR_UI, RenderMode::RM_UI);
	m_pHpBar->tf->m_vPos = Vector3(450, 120, 0);

	m_pExpBar_Bg = OBJ.Create("UI", Tag::UI);
	m_pExpBar_Bg->ac<CSpriteRenderer>()->Init(SPRITE("UI_PLAYERSTATUS_EXPBAR_BG"), SortingLayer::SR_UI, RenderMode::RM_UI);
	m_pExpBar_Bg->tf->m_vPos = Vector3(430, 150, 0);

	m_pExpBar = OBJ.Create("UI", Tag::UI);
	m_pExpBar->ac<CSpriteRenderer>()->Init(SPRITE("UI_PLAYERSTATUS_EXPBAR"), SortingLayer::SR_UI, RenderMode::RM_UI);
	m_pExpBar->tf->m_vPos = Vector3(430, 150, 0);


	CGameObject * Minimap = OBJ.Create();
	Minimap->ac<CSpriteRenderer>()->Init(SPRITE("UI_MINIMAP_STAGE01"), SortingLayer::SR_UI, RenderMode::RM_UI);
	Minimap->tf->m_vPos = Vector3(30, WINSIZEY - 30 - 350, 0);
	Minimap->gc<CSpriteRenderer>()->m_vAnchor = Vector2(0, 0);

	CurrentWeapon = OBJ.Create();
	CurrentWeapon->ac<CSpriteRenderer>()->Init(SPRITE("UI_ICON_PISTOL"), SortingLayer::SR_UI, RenderMode::RM_UI);
	CurrentWeapon->tf->m_vPos = Vector3(WINSIZEX -180, WINSIZEY - 100, 0);

	CGameObject * BulletSlash = OBJ.Create();
	BulletSlash->ac<CSpriteRenderer>()->Init(SPRITE("UI_BULLET_SLASH"), SortingLayer::SR_UI, RenderMode::RM_UI);
	BulletSlash->tf->m_vPos = Vector3(WINSIZEX - 350, WINSIZEY - 80, 0);

	CurrentBullet_Text = OBJ.Create();
	CurrentBullet_Text->ac<CText>()->Init("", SortingLayer::SR_UI, RenderMode::RM_UI);
	CurrentBullet_Text->tf->m_vPos = Vector3(WINSIZEX - 420, WINSIZEY - 130, 0);


	CGameObject * Skill01BG = OBJ.Create("UI", Tag::UI);
	Skill01BG->ac<CSpriteRenderer>()->Init(SPRITE("UI_SKILL_BACKGROUND"), SortingLayer::SR_UI, RenderMode::RM_UI, Color(1, 1, 1, 1.f));
	Skill01BG->tf->m_vPos = Vector3(800, WINSIZEY - 110, 0);

	CGameObject * Skill02BG = OBJ.Create("UI", Tag::UI);
	Skill02BG->ac<CSpriteRenderer>()->Init(SPRITE("UI_SKILL_BACKGROUND"), SortingLayer::SR_UI, RenderMode::RM_UI, Color(1, 1, 1, 1.f));
	Skill02BG->tf->m_vPos = Vector3(900, WINSIZEY - 110, 0);

	CGameObject * Skill03BG = OBJ.Create("UI", Tag::UI);
	Skill03BG->ac<CSpriteRenderer>()->Init(SPRITE("UI_SKILL_BACKGROUND"), SortingLayer::SR_UI, RenderMode::RM_UI, Color(1, 1, 1, 1.f));
	Skill03BG->tf->m_vPos = Vector3(1000, WINSIZEY - 110, 0);

	CGameObject * Skill04BG = OBJ.Create("UI", Tag::UI);
	Skill04BG->ac<CSpriteRenderer>()->Init(SPRITE("UI_SKILL_BACKGROUND"), SortingLayer::SR_UI, RenderMode::RM_UI, Color(1, 1, 1, 1.f));
	Skill04BG->tf->m_vPos = Vector3(1100, WINSIZEY - 110, 0);

	CGameObject * Skill01CoolTime = OBJ.Create("UI", Tag::UI);
	Skill01CoolTime->ac<CSpriteRenderer>()->Init(SPRITE("UI_SKILL_COOLTIME"), SortingLayer::SR_UI, RenderMode::RM_UI, Color(1, 1, 1, 1.f));
	Skill01CoolTime->tf->m_vPos = Vector3(800, WINSIZEY - 110, 0);

	CGameObject * Skill02CoolTime = OBJ.Create("UI", Tag::UI);
	Skill02CoolTime->ac<CSpriteRenderer>()->Init(SPRITE("UI_SKILL_COOLTIME"), SortingLayer::SR_UI, RenderMode::RM_UI, Color(1, 1, 1, 1.f));
	Skill02CoolTime->tf->m_vPos = Vector3(900, WINSIZEY - 110, 0);

	CGameObject * Skill03CoolTime = OBJ.Create("UI", Tag::UI);
	Skill01CoolTime->ac<CSpriteRenderer>()->Init(SPRITE("UI_SKILL_COOLTIME"), SortingLayer::SR_UI, RenderMode::RM_UI, Color(1, 1, 1, 1.f));
	Skill01CoolTime->tf->m_vPos = Vector3(1000, WINSIZEY - 110, 0);

	CGameObject * Skill04CoolTime = OBJ.Create("UI", Tag::UI);
	Skill02CoolTime->ac<CSpriteRenderer>()->Init(SPRITE("UI_SKILL_COOLTIME"), SortingLayer::SR_UI, RenderMode::RM_UI, Color(1, 1, 1, 1.f));
	Skill02CoolTime->tf->m_vPos = Vector3(1100, WINSIZEY - 110, 0);

	m_pSkill01 = OBJ.Create("UI", Tag::UI);
	m_pSkill01->ac<CSpriteRenderer>()->Init(SPRITE("UI_SKILL_01"), SortingLayer::SR_UI, RenderMode::RM_UI);
	m_pSkill01->tf->m_vPos = Vector3(800, WINSIZEY - 110, 0);

	m_pSkill02 = OBJ.Create("UI", Tag::UI);
	m_pSkill02->ac<CSpriteRenderer>()->Init(SPRITE("UI_SKILL_02"), SortingLayer::SR_UI, RenderMode::RM_UI);
	m_pSkill02->tf->m_vPos = Vector3(900, WINSIZEY - 110, 0);

	m_pSkill03 = OBJ.Create("UI", Tag::UI);
	m_pSkill03->ac<CSpriteRenderer>()->Init(SPRITE("UI_SKILL_03"), SortingLayer::SR_UI, RenderMode::RM_UI);
	m_pSkill03->tf->m_vPos = Vector3(1000, WINSIZEY - 110, 0);

	m_pSkill04 = OBJ.Create("UI", Tag::UI);
	m_pSkill04->ac<CSpriteRenderer>()->Init(SPRITE("UI_SKILL_04"), SortingLayer::SR_UI, RenderMode::RM_UI);
	m_pSkill04->tf->m_vPos = Vector3(1100, WINSIZEY - 110, 0);

	HavingBullet_Text = OBJ.Create();
	HavingBullet_Text->ac<CText>()->Init("", SortingLayer::SR_UI, RenderMode::RM_UI);
	HavingBullet_Text->tf->m_vPos = Vector3(WINSIZEX - 310, WINSIZEY - 130, 0);

	m_pLevelText = OBJ.Create();
	m_pLevelText->ac<CText>()->Init("", SortingLayer::SR_UI, RenderMode::RM_UI, Color(1, 1, 0
		, 1));
	m_pLevelText->tf->m_vPos = Vector3(150, 80, 0);
	m_pLevelText->tf->m_vScale = Vector3(0.8f, 0.8f, 0.8f);

	CGameObject * Timer = OBJ.Create();
	Timer->ac<CSpriteRenderer>()->Init(SPRITE("UI_TIME"), SortingLayer::SR_UI, RenderMode::RM_UI);
	Timer->tf->m_vPos = Vector3(WINSIZEX/2.F, 0 , 0);
	Timer->gc<CSpriteRenderer>()->m_vAnchor = Vector2(0.5f, 0);

	m_pTimer_Text = OBJ.Create();
	m_pTimer_Text->ac<CText>()->Init("", SortingLayer::SR_UI, RenderMode::RM_UI);
	m_pTimer_Text->tf->m_vPos = Vector3(WINSIZEX / 2.f - 140, 50, 0);
	m_pTimer_Text->tf->m_vScale = Vector3(0.75f, 0.75f, 0.f);
}

void CPlayerUI::Start()
{
}

void CPlayerUI::Update()
{
	GAME.m_fSkillTime[0]	+= dt;
		GAME.m_fSkillTime[1]+= dt;
		GAME.m_fSkillTime[2]+= dt;
		GAME.m_fSkillTime[3]+= dt;
	CurrentWeapon->gc<CSpriteRenderer>()->m_pSprite = GAME.m_pPlayer->gc<CPlayerMovement>()->m_iWeaponMode == 0 ? SPRITE("UI_ICON_PISTOL") : SPRITE("UI_ICON_RIFLE");


	CurrentBullet_Text->gc<CText>()->m_Text =
		to_string(GAME.m_iCurrentBullet[GAME.m_pPlayer->gc<CPlayerMovement>()->m_iWeaponMode]);

	if(GAME.m_pPlayer->gc<CPlayerMovement>()->m_iWeaponMode == 1)
	HavingBullet_Text->gc<CText>()->m_Text =
		to_string(GAME.m_iHavingBullet[GAME.m_pPlayer->gc<CPlayerMovement>()->m_iWeaponMode]);
	else
		HavingBullet_Text->gc<CText>()->m_Text =
		"∞";

	m_pHpBar->gc<CSpriteRenderer>()->m_vFillAmount = Lerp(m_pHpBar->gc<CSpriteRenderer>()->m_vFillAmount, Vector2((float)GAME.CurHp / (float)GAME.MaxHp, 1.f), dt * 32);
	m_pHpBar_Yellow->gc<CSpriteRenderer>()->m_vFillAmount = Lerp(m_pHpBar_Yellow->gc<CSpriteRenderer>()->m_vFillAmount, Vector2((float)GAME.CurHp / (float)GAME.MaxHp, 1.f), dt  * 2.f);

	m_pExpBar->gc<CSpriteRenderer>()->m_vFillAmount = Lerp(m_pExpBar->gc<CSpriteRenderer>()->m_vFillAmount, Vector2((float)GAME.CurExp / (float)GAME.MaxExp, 1.f), dt  * 4.f);
	m_pLevelText->gc<CText>()->m_Text = "Lv. " + to_string(GAME.Level);
	m_pTimer_Text->gc<CText>()->m_Text = "남은 시간 " + to_string((int)(GAME.Timer/60.f)) + " : " + to_string((int)((int)GAME.Timer % 60));
	
	m_pSkill01->gc<CSpriteRenderer>()->m_vFillAmount = Vector2(1.f, GAME.m_fSkillTime[0] / GAME.m_fSkillCoolTime[0]);
	m_pSkill02->gc<CSpriteRenderer>()->m_vFillAmount = Vector2(1.f, GAME.m_fSkillTime[1] / GAME.m_fSkillCoolTime[1]);
	m_pSkill03->gc<CSpriteRenderer>()->m_vFillAmount = Vector2(1.f, GAME.m_fSkillTime[2] / GAME.m_fSkillCoolTime[2]);
	m_pSkill04->gc<CSpriteRenderer>()->m_vFillAmount = Vector2(1.f, GAME.m_fSkillTime[3] / GAME.m_fSkillCoolTime[3]);

}

void CPlayerUI::LateUpdate()
{
}

void CPlayerUI::OnDestroy()
{
}

void CPlayerUI::OnRender()
{
	RenderPlayer(GAME.m_pPlayer);
	for (auto iter : OBJ.Finds(Tag::Enemy))
		RenderEnemy(iter);
}

void CPlayerUI::OnCollision(CGameObject * _pObject)
{
}

void CPlayerUI::RenderPlayer(CGameObject * _pPlayer)
{
	Vector3 vOffset = Vector3(45, WINSIZEY - 15 - 350, 0);
	Vector3 vPos = vOffset + Vector3(-_pPlayer->tf->m_vPos.x * 4, _pPlayer->tf->m_vPos.z * 4,0);
	GRAPHICS.Render_Sprite(SPRITE("UI_MINIMAP_PLAYER"), GRAPHICS.ToMatrix(vPos),Vector2(0.5f,0.5f), Vector2(1.f,1.f), Color(1,1,1,1), RenderMode::RM_UI);
}

void CPlayerUI::RenderEnemy(CGameObject * _pEnemy)
{
	Vector3 vOffset = Vector3(45, WINSIZEY - 15 - 350, 0);
	Vector3 vPos = vOffset + Vector3(-_pEnemy->tf->m_vPos.x * 4, _pEnemy->tf->m_vPos.z * 4, 0);
	GRAPHICS.Render_Sprite(SPRITE("UI_MINIMAP_ENEMY"), GRAPHICS.ToMatrix(vPos), Vector2(0.5f, 0.5f), Vector2(1.f, 1.f), Color(1, 1, 1, 1), RenderMode::RM_UI);

}



