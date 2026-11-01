# DX9_WorldSkill_Practice_Busan_01

2020 전국기능경기대회 부산 문제를 연습하며 만든 DirectX 9 기반 3D 슈팅 게임 프로젝트입니다. 플레이어를 따라가는 3인칭 카메라로 캐릭터를 조작해 권총·소총으로 몬스터를 쏘는 전투와 애니메이션, 이펙트가 구현되어 있고, 스테이지 진행과 승패 흐름은 아직 연결되지 않았습니다.

## 소개

- 저장소 설명: "2020 전국기능경기대회 부산 문제 연습"
- 커밋은 2020-08-30부터 2020-09-19까지 10건입니다. 서울디지텍고등학교 기능반(DirectX 게임 제작) 재학 시기에 해당합니다.
- 같은 시기의 `DX9_WorldSkill_Practice_Gyeonggi_01`과 엔진 코드 구성(컴포넌트, 애니메이터, 메시 로더)이 거의 같고, 게임 콘텐츠 부분만 다릅니다.

## 조작

| 입력 | 동작 |
|---|---|
| `W` `A` `S` `D` | 카메라 기준 이동 |
| `Left Shift` | 달리기 (걷기 속도의 1.75배) |
| 스페이스 | 대시 (이동 중, 잔상 효과) |
| 마우스 왼쪽 버튼 | 발사 (권총: 클릭마다, 소총: 누르고 있는 동안 연사) |
| `R` | 재장전 |
| `1` / `2` | 권총 / 소총 전환 |
| `Ctrl` 누르는 동안 | 플레이어 방향 고정 |
| `3`~`7`, `8`, `Z` | 개발용 테스트: 몬스터·보스 생성(3~7), 이펙트 연출(8), 장애물 생성(Z) |

## 핵심 구현

### 컴포넌트 구조 (`CGameObject`, `CComponent`, `CObjectManager`)

`CGameObject`에 `ac<T>()`(AddComponent), `gc<T>()`(GetComponent)로 `CTransform`, `CMeshRenderer`, `CCollider`, `CRigidBody`, `CAnimator3D` 같은 컴포넌트를 붙이는 구조입니다. 컴포넌트는 `Awake`, `Start`, `Update`, `LateUpdate`, `OnDestroy`, `OnCollision`을 구현하며, `CObjectManager::Update`가 `Start` 호출 -> `Update` -> 구 콜라이더 쌍 충돌 판정과 `OnCollision` 전달 -> `LateUpdate` -> 파괴 처리 순으로 돌립니다. 컴포넌트마다 `CScheduleAdmin`(`sa`)이 붙어 있어 "N초 뒤 실행", "보간이 끝날 때까지 반복" 같은 연출을 람다 큐로 처리합니다.

### 메시 시퀀스 애니메이션과 상태 머신 (`CAnimator3D`, `CPlayerMovement`)

모델은 프레임별 `.obj` 메시를 `키 (n)` 이름으로 등록하고, `CAnimator3D::AddState`가 번호를 올려 가며 모아 상태(예: `PISTOL_IDLE`, `RIFLE_RUN`)를 만듭니다. 플레이어는 무기(권총/소총)별로 IDLE, WALK, RUN, DASH, SHOOT, SKILL 상태를 두고, 현재 상태 이름에 무기 접두사를 붙여(`GetAnimationStateByWeapon() + "IDLE"`) 같은 로직으로 두 무기를 처리합니다. `SHOOT` 애니메이션의 4번째 프레임에 이벤트를 걸어 그 시점에 `FirePlayerBullet()`이 탄을 만들어 발사 모션과 탄 생성 타이밍을 맞춥니다.

```cpp
gc<CAnimator3D>()->AddState("PISTOL_SHOOT", "PLAYER_PISTOL_SHOOT", 10.f / 1000.f, false);
gc<CAnimator3D>()->AddState("RIFLE_SHOOT",  "PLAYER_RIFLE_SHOOT",  10.f / 1000.f, false);
gc<CAnimator3D>()->GetState("PISTOL_SHOOT")->AddEvent(4, [=]() { this->FirePlayerBullet(); });
gc<CAnimator3D>()->GetState("RIFLE_SHOOT")->AddEvent(4, [=]() { this->FirePlayerBullet(); });
```

### 사격과 탄약 (`CPlayerMovement`, `CGameManager`, `CPlayerBullet`)

무기별 발사 간격(권총 0.25초, 소총 0.1초), 탄 피해(권총 120, 소총 70), 장전 탄창(권총 6발, 소총 30발), 보유 탄약(소총 500발)을 `CGameManager::Reset`이 배열로 관리합니다. 발사 가능 여부(`CanFireBullet`)는 탄창이 남아 있고 마지막 발사 후 간격이 지났는지로 판정하고, 소총은 탄창이 비면 자동으로 재장전합니다. 탄은 `FirePlayerBullet`에서 캐릭터 회전 쿼터니언으로 총구 오프셋과 방향을 계산해 `CPlayerBullet`으로 생성합니다.

### 이동, 대시, 카메라

- 이동은 카메라 기준 축(`CAMERA.m_vCharactorAxis`)으로 방향을 구해 x와 z를 따로 이동시키며, 충돌 맵(`GetCollisionInfoByCollisionMap`)에서 벽이면 해당 축 이동을 취소합니다. 이렇게 하면 벽에 닿아도 벽면을 따라 미끄러집니다.
- 대시는 방향으로 초기 속도를 주고 매 프레임 감쇠시키며(0.3초), 0.025초마다 현재 메시를 복제한 반투명 오브젝트를 만들어 알파를 0으로 보간한 뒤 삭제하는 잔상 효과를 만듭니다.
- `CStage01`은 카메라 위치가 벽 영역에 들어가면 카메라 거리를 줄여 벽 뒤로 파고들지 않게 합니다.

### 몬스터 (`CEnemy`, `CEnemy01`~`03`, `CBoss01`, `CBoss02`, `CObstacle`)

- `CEnemy`: 체력, 이동 속도, 공격 사거리 등을 가진 공통 컴포넌트이며 체력 바와 이동·피격 처리를 담당합니다.
- `CEnemy01`: 목표를 향해 걷다가 사거리에 들어오면 크기를 키우고 빨갛게 변하며 폭발하는 자폭형입니다(`OnAttack`).
- `CEnemy02`는 공격 애니메이션 2종을 가지며, `CEnemy03`은 `CEnemyBullet`을 발사하는 원거리 몬스터이며, `CBoss01`/`CBoss02`는 등장(BORN), 공격 2종, 스킬, 사망 애니메이션을 가집니다.
- `CObstacle`: 지뢰(Mine), 가시(Thom), 함정(Trap) 3종의 장애물입니다.

### UI와 연출

`CPlayerUI`, `CDamageFont`(피해량), `CEffect`, `CButton`, `CText`, 보스 체력 바 등이 있습니다.

## 프로젝트 구조

| 경로 | 설명 |
|---|---|
| `CGameObject`, `CComponent`, `CObjectManager`, `CTransform`, `CCollider`, `CRigidBody`, `CScheduleAdmin` | 컴포넌트 구조, 충돌, 물리, 스케줄러 |
| `CAnimator3D`, `CAnimation3D`, `CMeshRenderer`, `MeshLoader` | 메시 시퀀스 애니메이션과 렌더링 |
| `CPlayerMovement`, `CPlayerBullet`, `CGameManager` | 플레이어, 사격, 게임 상태 |
| `CEnemy`, `CEnemy01~03`, `CBoss01`, `CBoss02`, `CEnemyBullet`, `CObstacle` | 몬스터, 보스, 장애물 |
| `CStage01`, `CStage02`, `CStageMap`, `CTitleScene`, `CStageClear`, `CGameClear`, `CGameOver` | 씬과 지형 |
| `CPlayerUI`, `CDamageFont`, `CEffect`, `CItem` | UI, 이펙트, 아이템 |
| `Resource/` | 모델(OBJ/FBX), UI, 이펙트, 사운드 |
| `EmptyProject_2010.sln` | Visual Studio 솔루션 (소스는 저장소 최상위) |

## 기술 스택

- C++, DirectX 9, DXUT(저장소에 포함)
- Visual Studio 프로젝트 `EmptyProject_2010.sln`: 플랫폼 도구 집합 v141

## 실행 방법

1. Visual Studio(v141 도구 집합)와 DirectX SDK가 필요합니다. 프로젝트가 `DXSDK_DIR` 환경 변수를 참조합니다.
2. `EmptyProject_2010.sln`을 열어 빌드합니다. 리소스는 `Resource/` 폴더에서 상대 경로로 읽습니다.

빌드는 당시 환경 기준입니다.

## 현재 상태

대회 문제 연습용 학습 프로젝트이며 2020-09-19 이후 갱신이 없습니다. 코드에서 확인되는 미완성 부분은 다음과 같습니다.

- 시작 씬이 `S_STAGE01`이고, 몬스터를 생성하는 코드는 테스트 키(`3`~`7`)뿐입니다. 자동 스폰이나 웨이브가 없습니다.
- `CStage01`은 제한 시간(180초)을 줄여 나가기만 하고 시간이 다 돼도 다른 씬으로 넘어가지 않습니다. `S_STAGECLEAR`, `S_GAMECLEAR`, `S_GAMEOVER`로 전환하는 코드가 없고 `CStage02`는 비어 있습니다.
- 적 탄이 플레이어에 닿으면 이펙트만 나오고 플레이어 체력이 줄어드는 처리는 확인되지 않습니다.
- `Resource/`(모델, UI, 이펙트, 사운드)에는 외부에서 받은 것으로 보이는 에셋이 포함되어 있고 출처는 저장소에 기록되어 있지 않습니다.
