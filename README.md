# FullMoon

멀티플레이 로그라이트 액션 RPG 게임

장르 : 멀티플레이 로그라이트 액션 RPG

엔진 : Unreal Engine 5.4 / C++

개발 기간 : 2024.09 ~ 

개발 인원 : 1인 개발

프로젝트 파일 : Content 폴더의 아트 에셋 제외



<hr/>

### 프로젝트 소개

- 몬스터를 잡아 스테이지를 클리어하며, 마지막 보스를 처치하는 것이 최종 목표

- 파밍을 통해 일시적/영구적 능력치 성장 가능


<hr/>

### 프로젝트 개발 목표

- 액션 RPG의 핵심인 쫀득한 타격감을 위해 정밀한 타격 판정 시스템 구현

- 부정 행위 방지를 위해 서버 권위적으로 게임 핵심 로직 처리

- 조작감 향상을 위해 일부 로직은 Client-Side Prediction & Server Reconciliation 방식으로 구현

- 의존성을 줄이며, 데이터 주도형 게임을 목표로 구현



<hr/>

### 핵심 개발 기능

1. 공격 시스템 - 멀티플레이 공격 시스템 구조, 공격 판정 개선, 중복 제거 및 HitStop
2. 스킬 시스템 - 스킬 시스템 구조, 쿨타임 계산
3. 아이템 및 인벤토리 시스템 - 아이템 시스템 구조, 상호작용, 인벤토리 시스템
4. AI - AI 스킬 발동 시스템, AI 스킬 디버그 에디터
5. 캐릭터 애니메이션 - 애니메이션 레이어
6. 이펙트 및 UI - 공격 범위 데칼, Layered HP Bar




<hr/>

### 프로젝트 소스 디렉토리 구조

#### AI
- AI 디렉토리
- AI Controller, AI Data
- Behavior Tree의 Task, Decorator, Service

#### Animation
- 애니메이션 디렉토리
- AnimInstance, AnimNotify, AnimNotifyState

#### Character
- 캐릭터 디렉토리
- Player 캐릭터, AI 캐릭터

#### Combat
- 전투 컴포넌트
- 무기, 스킬 컴포넌트와 같이 전투와 관련된 기능 관리

#### DataStructure
- 자료구조
- 스킬 쿨타임 계산을 위해 제작한 Priority List

#### Game
- 게임 프레임워크 디렉토리
- GameMode, GameState

#### GameData
- 게임 데이터 관련 디렉토리
- 에셋 매니저, 게임 데이터 관리 싱글톤 클래스

#### Input
- 플레이어 입력 Mapping Context, Input Action 관리

#### Interface
- 인터페이스 디렉토리
- 게임 내 사용되는 인터페이스들을 모아둠

#### Inventory
- 인벤토리 컴포넌트
- 획득한 아이템 인벤토리에 추가 가능

#### Item
- 아이템 액터 클래스
- 월드에 스폰되는 아이템 관련 클래스

#### ItemData
- 아이템 데이터 클래스
- 아이템 데이터 정보가 담긴 DataAsset 관련 클래스

#### Physics
- 충돌 검사 관련 기능들이 정의된 클래스

#### Skill
- 스킬 디렉토리
- 스킬을 관리하는 스킬 컴포넌트, 스킬 데이터 관련 클래스

#### Stat
- 스탯 컴포넌트

#### UI
- UI 디렉토리
- UI 관련 기능 관리

