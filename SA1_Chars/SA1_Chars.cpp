#include "stdafx.h"
#include "Sonic.h"
#include "Tails.h"
#include "Knuckles.h"
#include "EV_TR1.h"
#include "OBJECT_SonicPointingFinger.h"
#include "EV_TR2BEFORE.h"
#include "EV_TR2CHANGE.h"
#include "SkyChase.h"
#include "EV_TailsIntro.h"
#include "Big.h"
#include "Amy.h"
#include "e102.h"
#include "Tikal.h"
#include "Eggman.h"
#include <cmath>

static NJS_OBJECT **SONIC_OBJECTS = nullptr;
static NJS_ACTION **SONIC_ACTIONS = nullptr;
static NJS_MODEL_SADX **SONIC_MODELS = nullptr;
static NJS_MOTION **SONIC_MOTIONS = nullptr;

static NJS_OBJECT **MILES_OBJECTS = nullptr;
static NJS_ACTION **MILES_ACTIONS = nullptr;
static NJS_MODEL_SADX **MILES_MODELS = nullptr;
static NJS_MOTION **MILES_MOTIONS = nullptr;

static NJS_OBJECT **KNUCKLES_OBJECTS = nullptr;
static NJS_ACTION **KNUCKLES_ACTIONS = nullptr;
static NJS_MODEL_SADX **KNUCKLES_MODELS = nullptr;
static NJS_MOTION **KNUCKLES_MOTIONS = nullptr;

static NJS_OBJECT **AMY_OBJECTS = nullptr;
static NJS_ACTION **AMY_ACTIONS = nullptr;
static NJS_MODEL_SADX **AMY_MODELS = nullptr;
static NJS_MOTION **AMY_MOTIONS = nullptr;

static NJS_OBJECT **BIG_OBJECTS = nullptr;
static NJS_ACTION **BIG_ACTIONS = nullptr;
static NJS_MODEL_SADX **BIG_MODELS = nullptr;
static NJS_MOTION **BIG_MOTIONS = nullptr;

DataPointer(int, dword_3C53274, 0x03C53274);
DataPointer(int, dword_3C5325C, 0x03C5325C);
DataPointer(int, dword_3C53154, 0x03C53254);
DataPointer(int, dword_3C5313C, 0x03C5313C);

DataArray(WeldInfo, SonicWeldInfo, 0x03C55E28, 0x25);
DataArray(WeldInfo, NPCSonicWeldInfo, 0x03C56B50, 0x10);
DataArray(WeldInfo, TailsWeldInfo, 0x03C4A610, 0x1E);
DataArray(WeldInfo, NPCTailsWeldInfo, 0x03C4A938, 0x19);
DataArray(WeldInfo, KnucklesWeldInfo, 0x03C52D68, 0x1E);
DataArray(WeldInfo, NPCKnucklesWeldInfo, 0x03C53038, 0x19);
DataArray(WeldInfo, AmyWeldInfo, 0x03C546D0, 0x12);
DataArray(WeldInfo, NPCAmyWeldInfo, 0x03C54EE0, 0x0D);
DataArray(WeldInfo, BigWeldInfo, 0x03C55500, 0x11);

ObjectFunc(Tails_Jiggle_Delete, 0x0045B810);
DataArray(EntityData2*, EntityData2Ptrs, 0x03B36DD0, 8);
FunctionPointer(void, MorphPoints, (NJS_MODEL_SADX *a, NJS_MODEL_SADX *b, NJS_MODEL_SADX *destination, float factor), 0x00439F20);
FunctionPointer(void, sub_4083D0, (NJS_ACTION *a1, float a2, int a3), 0x004083D0);

void __cdecl Sonic_MorphStretchyFeet_c(CharObj2* a1)
{
	float a4; // ST10_4@3
	float v2; // ST10_4@5
	NJS_MODEL_SADX *v3; // ecx@5
	float v4; // ST10_4@10
	float v5; // ST10_4@13

	if (a1->Upgrades & Upgrades_LightShoes)
	{
		if (a1->AnimationThing.Index == 13)
		{
			if (a1->AnimationThing.Frame >= 16.0)
			{
				if (a1->AnimationThing.Frame <= 24.0)
				{
					a1->SomeFrameNumberThing = 0;
					v3 = &LSDashMorph_Left3;
				}
				else
				{
					v2 = (a1->AnimationThing.Frame - 24.0) * 0.125;
					a1->SomeFrameNumberThing = v2;
					MorphPoints(&LSDashMorph_Left3, &LSDashMorph_Left2, &LSDashMorph_Left1, v2);
					v3 = &LSDashMorph_Left1;
				}
				object_005818AC.model = v3;
			}
			else
			{
				a4 = (16.0 - a1->AnimationThing.Frame) * 0.0625;
				a1->SomeFrameNumberThing = a4;
				MorphPoints(&LSDashMorph_Left3, &LSDashMorph_Left2, &LSDashMorph_Left1, a4);
				object_005818AC.model = &LSDashMorph_Left1;
			}
			if (a1->AnimationThing.Frame < 8.0 || a1->AnimationThing.Frame > 16.0)
			{
				if (a1->AnimationThing.Frame <= 16.0 || a1->AnimationThing.Frame > 32.0)
				{
					a1->TailsFlightTime = 0;
					object_005825A4.model = &LSDashMorph_Right2;
				}
				else
				{
					v5 = (32.0 - a1->AnimationThing.Frame) * 0.0625;
					a1->TailsFlightTime = v5;
					MorphPoints(&LSDashMorph_Right2, &LSDashMorph_Right3, &LSDashMorph_Right1, v5);
					object_005825A4.model = &LSDashMorph_Right1;
				}
			}
			else
			{
				v4 = (a1->AnimationThing.Frame - 8.0) * 0.125;
				a1->TailsFlightTime = v4;
				MorphPoints(&LSDashMorph_Right2, &LSDashMorph_Right3, &LSDashMorph_Right1, v4);
				object_005825A4.model = &LSDashMorph_Right1;
			}
		}
		else
		{
			a1->SomeFrameNumberThing = 0;
			a1->TailsFlightTime = 0;
			object_005818AC.model = &attach_00581880;
			object_005825A4.model = &attach_00582578;
		}
	}
	else
	{
		if (a1->AnimationThing.Index == 13)
		{
			if (a1->AnimationThing.Frame >= 16.0)
			{
				if (a1->AnimationThing.Frame <= 24.0)
				{
					a1->SomeFrameNumberThing = 0;
					v3 = &attach_0057464C;
				}
				else
				{
					v2 = (a1->AnimationThing.Frame - 24.0) * 0.125;
					a1->SomeFrameNumberThing = v2;
					MorphPoints(&attach_0057464C, &attach_00573DFC, &attach_005735AC, v2);
					v3 = &attach_005735AC;
				}
				object_0055F330.model = v3;
			}
			else
			{
				a4 = (16.0 - a1->AnimationThing.Frame) * 0.0625;
				a1->SomeFrameNumberThing = a4;
				MorphPoints(&attach_0057464C, &attach_00573DFC, &attach_005735AC, a4);
				object_0055F330.model = &attach_005735AC;
			}
			if (a1->AnimationThing.Frame < 8.0 || a1->AnimationThing.Frame > 16.0)
			{
				if (a1->AnimationThing.Frame <= 16.0 || a1->AnimationThing.Frame > 32.0)
				{
					a1->TailsFlightTime = 0;
					object_00560DD0.model = &attach_00575AB4;
				}
				else
				{
					v5 = (32.0 - a1->AnimationThing.Frame) * 0.0625;
					a1->TailsFlightTime = v5;
					MorphPoints(&attach_00575AB4, &attach_0057630C, &attach_0057525C, v5);
					object_00560DD0.model = &attach_0057525C;
				}
			}
			else
			{
				v4 = (a1->AnimationThing.Frame - 8.0) * 0.125;
				a1->TailsFlightTime = v4;
				MorphPoints(&attach_00575AB4, &attach_0057630C, &attach_0057525C, v4);
				object_00560DD0.model = &attach_0057525C;
			}
		}
		else
		{
			a1->SomeFrameNumberThing = 0;
			a1->TailsFlightTime = 0;
			object_0055F330.model = &attach_0055F304;
			object_00560DD0.model = &attach_00560DA4;
		}
	}
}

static void __declspec(naked) Sonic_MorphStretchyFeet_asm()
{
	__asm
	{
		push esi // a1
		call Sonic_MorphStretchyFeet_c
		pop esi // a1
		retn
	}
}

const Sint16 MorphVertsT[] = {
	// right ear
	28, 188, 56, 200,
	// left ear
	99, 228, 127, 193,
	// hair (top, middle, bottom)
	169, 176, 162,
	// right whiskers
	9, 1, 3, 7,
	// left whiskers
	80, 72, 74, 78
};

static void __cdecl Tails_Jiggle_Main(ObjectMaster *_this)
{
	NJS_POINT3 *_src_points; // esi@4
	float v21; // st7@32
	Sint32 nbPoint; // [sp+14h] [bp-14h]@4
	NJS_VECTOR a2; // [sp+1Ch] [bp-Ch]@29

	EntityData2* v1 = (EntityData2*)_this->Data2;
	EntityData1* v2 = _this->Data1;
	int v3 = v2->CharIndex;

	if (!CharObj1Ptrs[v3])
	{
		CheckThingButThenDeleteObject(_this);
		return;
	}

	EntityData2 *v25 = EntityData2Ptrs[v3];
	CharObj2 *v4 = GetCharObj2(v2->CharIndex);
	NJS_POINT3 *_dst_points = MILES_MODELS[4]->points;
	NJS_OBJECT *v6 = TailsAnimData[v4->AnimationThing.Index].Animation->object;

	if (v6 == *MILES_OBJECTS)
	{
		NJS_MODEL_SADX *v7 = MILES_MODELS[2];
		_src_points = v7->points;
		nbPoint = v7->nbPoint;
	}
	else
	{
		if (v6 != MILES_OBJECTS[1])
		{
			return;
		}

		NJS_MODEL_SADX *v9 = MILES_MODELS[3];
		_src_points = v9->points;
		nbPoint = v9->nbPoint;
	}

	if (!v2->Action)
	{
		v2->Action = 1;
		_this->DeleteSub = Tails_Jiggle_Delete;
	}
	else if (v2->Action == 1)
	{
		float v10 = v25->VelocityDirection.x * v25->VelocityDirection.x
			+ v25->VelocityDirection.y * v25->VelocityDirection.y
			+ v25->VelocityDirection.z * v25->VelocityDirection.z;
		float v11 = squareroot(v10);
		float v12 = v11 + v11;

		if (fabs(v1->VelocityDirection.y) < v12)
		{
			if (v12 < 0.0f)
			{
				v12 = -v12;
			}
			if (v12 > 4.0f)
			{
				v12 = 4.0f;
			}
			v1->VelocityDirection.y = v12;
		}

		if (v1->VelocityDirection.y >= 0.2f || v1->VelocityDirection.y <= -0.2f)
		{
			v1->VelocityDirection.y = v1->VelocityDirection.y * 0.99000001f;
		}
		else
		{
			v1->VelocityDirection.y = 0.0f;
		}

		signed int v13 = (int)fabs(v1->VelocityDirection.y * 512.0f) + 2048;
		if (v13 > 3072)
		{
			v13 = 3072;
		}

		Angle v14 = v13 + v1->field_30;
		v1->field_30 = v14;
		v2->Rotation.z = (int)(v1->VelocityDirection.y * 0.2f * njCos(v14) * 4096.0f);

		njUnitMatrix(TailsMatrix1);
		Angle v15 = v2->Rotation.z;
		if (v15)
		{
			njRotateZ(TailsMatrix1, (unsigned __int16)v15);
		}

		njUnitMatrix(TailsMatrix2);
		Angle v16 = v2->Rotation.z >> 1;
		if (v16)
		{
			njRotateZ(TailsMatrix2, (unsigned __int16)v16);
		}

		if (nbPoint)
		{
			for (auto i : MorphVertsT)
			{
				auto src_points = &_src_points[i - 1];
				auto dst_points = &_dst_points[i - 1];

				if (src_points->y >= -2.9000001f)
				{
					if (src_points->y <= -1.65f || fabs(src_points->z) <= 1.15f)
					{
						if (src_points->y >= -2.0999999f || src_points->x <= 1.3f)
						{
							continue;
						}

						float v22 = src_points->x + 0.25f;
						float v23 = src_points->y;
						a2.z = src_points->z;
						a2.x = v22;
						a2.y = v23;
						njCalcVector(TailsMatrix2, &a2, dst_points);
						v21 = dst_points->x - 0.25f;
					}
					else
					{
						float v19 = src_points->z;
						float v20 = src_points->x + 1.5f;
						a2.y = src_points->y;
						a2.z = v19;
						a2.x = v20;
						njCalcVector(TailsMatrix1, &a2, dst_points);
						v21 = dst_points->x - 1.5f;
					}
					dst_points->x = v21;
				}
				else
				{
					float v18 = src_points->z;
					a2.x = src_points->x + 0.5f;
					a2.z = v18;
					a2.y = src_points->y + 1.5f;
					njCalcVector(TailsMatrix1, &a2, dst_points);
					dst_points->x = dst_points->x - 0.5f;
					dst_points->y = dst_points->y - 1.5f;
				}
			}
		}
	}
	else
	{
		DeleteObjectMaster(_this);
	}

	MILES_OBJECTS[4]->model = MILES_MODELS[4];
	MILES_OBJECTS[5]->model = MILES_MODELS[4];
}

void __cdecl InitSonicWeldInfo_mod()
{
	NJS_OBJECT *v0; // ebp@1
	NJS_OBJECT *v1; // ebp@1
	NJS_OBJECT *v2; // ebp@1
	NJS_OBJECT *v3; // ebp@1
	NJS_OBJECT *v4; // edi@1
	NJS_OBJECT *v5; // eax@1

					//The following welds are for Sonic
	SonicWeldInfo[0].BaseModel = SONIC_OBJECTS[0];
	SonicWeldInfo[0].ModelA = SONIC_OBJECTS[1];
	SonicWeldInfo[0].ModelB = SONIC_OBJECTS[2];
	SonicWeldInfo[0].anonymous_5 = 0;
	SonicWeldInfo[0].VertexBuffer = 0;
	SonicWeldInfo[0].VertexPairCount = (uint8_t)(LengthOfArray(Sonic_UpperArmIndices) / 2);
	SonicWeldInfo[0].WeldType = 2;
	SonicWeldInfo[0].VertIndexes = Sonic_UpperArmIndices;
	SonicWeldInfo[1].BaseModel = SONIC_OBJECTS[0];
	SonicWeldInfo[1].ModelA = SONIC_OBJECTS[2];
	SonicWeldInfo[1].ModelB = SONIC_OBJECTS[3];
	SonicWeldInfo[1].VertexPairCount = (uint8_t)(LengthOfArray(Sonic_LowerArmIndices) / 2);
	SonicWeldInfo[1].WeldType = 2;
	SonicWeldInfo[1].anonymous_5 = 0;
	SonicWeldInfo[1].VertexBuffer = 0;
	SonicWeldInfo[1].VertIndexes = Sonic_LowerArmIndices;
	SonicWeldInfo[2].BaseModel = SONIC_OBJECTS[0];
	SonicWeldInfo[2].ModelA = SONIC_OBJECTS[7];
	SonicWeldInfo[2].ModelB = SONIC_OBJECTS[8];
	SonicWeldInfo[2].VertexPairCount = (uint8_t)(LengthOfArray(Sonic_UpperArmIndices) / 2);
	SonicWeldInfo[2].WeldType = 2;
	SonicWeldInfo[2].anonymous_5 = 0;
	SonicWeldInfo[2].VertexBuffer = 0;
	SonicWeldInfo[2].VertIndexes = Sonic_UpperArmIndices;
	SonicWeldInfo[3].BaseModel = SONIC_OBJECTS[0];
	SonicWeldInfo[3].ModelA = SONIC_OBJECTS[8];
	v0 = SONIC_OBJECTS[9];
	SonicWeldInfo[3].VertIndexes = Sonic_LowerArmIndices;
	SonicWeldInfo[3].ModelB = v0;
	SonicWeldInfo[3].VertexPairCount = (uint8_t)(LengthOfArray(Sonic_LowerArmIndices) / 2);
	SonicWeldInfo[3].WeldType = 2;
	SonicWeldInfo[3].anonymous_5 = 0;
	SonicWeldInfo[3].VertexBuffer = 0;
	SonicWeldInfo[4].BaseModel = SONIC_OBJECTS[0];
	SonicWeldInfo[4].ModelA = SONIC_OBJECTS[12];
	SonicWeldInfo[4].ModelB = SONIC_OBJECTS[13];
	SonicWeldInfo[4].VertexPairCount = (uint8_t)(LengthOfArray(Sonic_UpperLegIndices) / 2);
	SonicWeldInfo[4].WeldType = 2;
	SonicWeldInfo[4].anonymous_5 = 0;
	SonicWeldInfo[4].VertexBuffer = 0;
	SonicWeldInfo[4].VertIndexes = Sonic_UpperLegIndices;
	SonicWeldInfo[5].BaseModel = SONIC_OBJECTS[0];
	SonicWeldInfo[5].ModelA = SONIC_OBJECTS[13];
	SonicWeldInfo[5].ModelB = SONIC_OBJECTS[14];
	SonicWeldInfo[5].VertexPairCount = (uint8_t)(LengthOfArray(Sonic_LowerLegIndices) / 2);
	SonicWeldInfo[5].WeldType = 2;
	SonicWeldInfo[5].anonymous_5 = 0;
	SonicWeldInfo[5].VertexBuffer = 0;
	SonicWeldInfo[5].VertIndexes = Sonic_LowerLegIndices;
	SonicWeldInfo[6].BaseModel = SONIC_OBJECTS[0];
	SonicWeldInfo[6].ModelA = SONIC_OBJECTS[17];
	v1 = SONIC_OBJECTS[18];
	SonicWeldInfo[6].VertIndexes = Sonic_UpperLegIndices;
	SonicWeldInfo[6].ModelB = v1;
	SonicWeldInfo[6].VertexPairCount = (uint8_t)(LengthOfArray(Sonic_UpperLegIndices) / 2);
	SonicWeldInfo[6].WeldType = 2;
	SonicWeldInfo[6].anonymous_5 = 0;
	SonicWeldInfo[6].VertexBuffer = 0;
	SonicWeldInfo[7].BaseModel = SONIC_OBJECTS[0];
	SonicWeldInfo[7].ModelA = SONIC_OBJECTS[18];
	SonicWeldInfo[7].ModelB = SONIC_OBJECTS[19];
	SonicWeldInfo[7].VertexPairCount = (uint8_t)(LengthOfArray(Sonic_LowerLegIndices) / 2);
	SonicWeldInfo[7].WeldType = 2;
	SonicWeldInfo[7].anonymous_5 = 0;
	SonicWeldInfo[7].VertexBuffer = 0;
	SonicWeldInfo[7].VertIndexes = Sonic_LowerLegIndices;
	SonicWeldInfo[8].BaseModel = SONIC_OBJECTS[0];
	SonicWeldInfo[8].ModelA = SONIC_OBJECTS[15];
	SonicWeldInfo[8].ModelB = SONIC_OBJECTS[16];
	SonicWeldInfo[8].VertexPairCount = (uint8_t)(LengthOfArray(Sonic_ShoeIndices) / 2);
	SonicWeldInfo[8].WeldType = 2;
	SonicWeldInfo[8].anonymous_5 = 0;
	SonicWeldInfo[8].VertexBuffer = 0;
	SonicWeldInfo[8].VertIndexes = Sonic_ShoeIndices;
	SonicWeldInfo[9].BaseModel = SONIC_OBJECTS[0];
	SonicWeldInfo[9].ModelA = SONIC_OBJECTS[20];
	v2 = SONIC_OBJECTS[21];
	SonicWeldInfo[9].VertIndexes = Sonic_ShoeIndices;
	SonicWeldInfo[9].ModelB = v2;
	SonicWeldInfo[9].VertexPairCount = (uint8_t)(LengthOfArray(Sonic_ShoeIndices) / 2);
	SonicWeldInfo[9].WeldType = 2;
	SonicWeldInfo[9].anonymous_5 = 0;
	SonicWeldInfo[9].VertexBuffer = 0;
	SonicWeldInfo[10].BaseModel = SONIC_OBJECTS[0];
	SonicWeldInfo[10].ModelA = SONIC_OBJECTS[10];
	SonicWeldInfo[10].ModelB = SONIC_OBJECTS[11];
	SonicWeldInfo[10].VertexPairCount = (uint8_t)(LengthOfArray(Sonic_HandIndices) / 2);
	SonicWeldInfo[10].WeldType = 2;
	SonicWeldInfo[10].anonymous_5 = 0;
	SonicWeldInfo[10].VertexBuffer = 0;
	SonicWeldInfo[10].VertIndexes = Sonic_HandIndices;
	SonicWeldInfo[11].BaseModel = SONIC_OBJECTS[0];
	SonicWeldInfo[11].ModelA = SONIC_OBJECTS[4];
	SonicWeldInfo[11].ModelB = SONIC_OBJECTS[5];
	SonicWeldInfo[11].VertexPairCount = (uint8_t)(LengthOfArray(Sonic_HandIndices) / 2);
	SonicWeldInfo[11].WeldType = 2;
	SonicWeldInfo[11].anonymous_5 = 0;
	SonicWeldInfo[11].VertexBuffer = 0;
	SonicWeldInfo[11].VertIndexes = Sonic_HandIndices;
	SonicWeldInfo[12].BaseModel = SONIC_OBJECTS[0];
	SonicWeldInfo[12].ModelA = SONIC_OBJECTS[58];
	SonicWeldInfo[12].ModelB = SONIC_OBJECTS[59];
	SonicWeldInfo[12].VertexPairCount = (uint8_t)(LengthOfArray(Sonic_ShoeIndices) / 2);
	SonicWeldInfo[12].WeldType = 2;
	SonicWeldInfo[12].anonymous_5 = 0;
	SonicWeldInfo[12].VertexBuffer = 0;
	SonicWeldInfo[12].VertIndexes = Sonic_ShoeIndices;
	SonicWeldInfo[13].BaseModel = SONIC_OBJECTS[0];
	SonicWeldInfo[13].ModelA = SONIC_OBJECTS[60];
	SonicWeldInfo[13].ModelB = SONIC_OBJECTS[61];
	SonicWeldInfo[13].VertexPairCount = (uint8_t)(LengthOfArray(Sonic_ShoeIndices) / 2);
	SonicWeldInfo[13].WeldType = 2;
	SonicWeldInfo[13].anonymous_5 = 0;
	SonicWeldInfo[13].VertexBuffer = 0;
	SonicWeldInfo[13].VertIndexes = Sonic_ShoeIndices;
	SonicWeldInfo[14].BaseModel = SONIC_OBJECTS[0];
	SonicWeldInfo[14].ModelA = SONIC_OBJECTS[2];
	SonicWeldInfo[14].ModelB = SONIC_OBJECTS[63];
	SonicWeldInfo[14].VertexPairCount = (uint8_t)(LengthOfArray(Sonic_LowerArmIndices) / 2);
	SonicWeldInfo[14].WeldType = 2;
	SonicWeldInfo[14].anonymous_5 = 0;
	SonicWeldInfo[14].VertexBuffer = 0;
	SonicWeldInfo[14].VertIndexes = Sonic_LowerArmIndices;
	SonicWeldInfo[15].BaseModel = SONIC_OBJECTS[0];
	SonicWeldInfo[15].ModelA = SONIC_OBJECTS[5];
	SonicWeldInfo[15].ModelB = 0;
	SonicWeldInfo[15].VertexPairCount = 2;
	SonicWeldInfo[15].WeldType = 4;
	SonicWeldInfo[15].anonymous_5 = 0;
	SonicWeldInfo[15].VertexBuffer = 0;
	SonicWeldInfo[15].VertIndexes = 0;
	SonicWeldInfo[16].BaseModel = SONIC_OBJECTS[0];
	SonicWeldInfo[16].ModelA = SONIC_OBJECTS[11];
	SonicWeldInfo[16].ModelB = 0;
	SonicWeldInfo[16].VertexPairCount = 2;
	SonicWeldInfo[16].WeldType = 5;
	SonicWeldInfo[16].anonymous_5 = 0;
	SonicWeldInfo[16].VertexBuffer = 0;
	SonicWeldInfo[16].VertIndexes = 0;
	SonicWeldInfo[17].BaseModel = SONIC_OBJECTS[0];
	SonicWeldInfo[17].ModelA = SONIC_OBJECTS[59];
	SonicWeldInfo[17].ModelB = 0;
	SonicWeldInfo[17].VertexPairCount = 0;
	SonicWeldInfo[17].WeldType = 7;
	SonicWeldInfo[17].anonymous_5 = 0;
	SonicWeldInfo[17].VertexBuffer = 0;
	SonicWeldInfo[17].VertIndexes = 0;
	SonicWeldInfo[18].BaseModel = SONIC_OBJECTS[0];
	SonicWeldInfo[18].ModelA = SONIC_OBJECTS[61];
	SonicWeldInfo[18].ModelB = 0;
	SonicWeldInfo[18].VertexPairCount = 0;
	SonicWeldInfo[18].WeldType = 6;
	SonicWeldInfo[18].anonymous_5 = 0;
	SonicWeldInfo[18].VertexBuffer = 0;
	SonicWeldInfo[18].VertIndexes = 0;
	SonicWeldInfo[19].BaseModel = SONIC_OBJECTS[0];
	SonicWeldInfo[19].ModelA = SONIC_OBJECTS[16];
	SonicWeldInfo[19].ModelB = 0;
	SonicWeldInfo[19].VertexPairCount = 0;
	SonicWeldInfo[19].WeldType = 6;
	SonicWeldInfo[19].anonymous_5 = 0;
	SonicWeldInfo[19].VertexBuffer = 0;
	SonicWeldInfo[19].VertIndexes = 0;
	SonicWeldInfo[20].BaseModel = SONIC_OBJECTS[0];
	SonicWeldInfo[20].ModelA = SONIC_OBJECTS[21];
	SonicWeldInfo[20].ModelB = 0;
	SonicWeldInfo[20].VertexPairCount = 0;
	SonicWeldInfo[20].WeldType = 7;
	SonicWeldInfo[20].anonymous_5 = 0;
	SonicWeldInfo[20].VertexBuffer = 0;
	SonicWeldInfo[20].VertIndexes = 0;
	SonicWeldInfo[21].BaseModel = SONIC_OBJECTS[0];
	SonicWeldInfo[21].ModelA = SONIC_OBJECTS[45];
	SonicWeldInfo[21].ModelB = 0;
	SonicWeldInfo[21].VertexPairCount = 0;
	SonicWeldInfo[21].WeldType = 8;
	SonicWeldInfo[21].anonymous_5 = 0;
	SonicWeldInfo[21].VertexBuffer = 0;
	SonicWeldInfo[21].VertIndexes = 0;

	//The following welds are for Super Sonic
	SonicWeldInfo[22].BaseModel = SONIC_OBJECTS[22];
	SonicWeldInfo[22].ModelA = SONIC_OBJECTS[23];
	SonicWeldInfo[22].ModelB = SONIC_OBJECTS[24];
	SonicWeldInfo[22].VertexPairCount = (uint8_t)(LengthOfArray(Sonic_UpperArmIndices) / 2);
	SonicWeldInfo[22].WeldType = 2;
	SonicWeldInfo[22].anonymous_5 = 0;
	SonicWeldInfo[22].VertexBuffer = 0;
	SonicWeldInfo[22].VertIndexes = Sonic_UpperArmIndices;
	SonicWeldInfo[23].BaseModel = SONIC_OBJECTS[22];
	SonicWeldInfo[23].ModelA = SONIC_OBJECTS[24];
	SonicWeldInfo[23].ModelB = SONIC_OBJECTS[25];
	SonicWeldInfo[23].VertexPairCount = (uint8_t)(LengthOfArray(Sonic_LowerArmIndices) / 2);
	SonicWeldInfo[23].WeldType = 2;
	SonicWeldInfo[23].anonymous_5 = 0;
	SonicWeldInfo[23].VertexBuffer = 0;
	SonicWeldInfo[23].VertIndexes = Sonic_LowerArmIndices;
	SonicWeldInfo[24].BaseModel = SONIC_OBJECTS[22];
	SonicWeldInfo[24].ModelA = SONIC_OBJECTS[28];
	SonicWeldInfo[24].ModelB = SONIC_OBJECTS[29];
	SonicWeldInfo[24].VertexPairCount = (uint8_t)(LengthOfArray(Sonic_UpperArmIndices) / 2);
	SonicWeldInfo[24].WeldType = 2;
	SonicWeldInfo[24].anonymous_5 = 0;
	SonicWeldInfo[24].VertexBuffer = 0;
	SonicWeldInfo[24].VertIndexes = Sonic_UpperArmIndices;
	SonicWeldInfo[25].BaseModel = SONIC_OBJECTS[22];
	SonicWeldInfo[25].ModelA = SONIC_OBJECTS[29];
	SonicWeldInfo[25].ModelB = SONIC_OBJECTS[30];
	SonicWeldInfo[25].VertexPairCount = (uint8_t)(LengthOfArray(Sonic_LowerArmIndices) / 2);
	SonicWeldInfo[25].WeldType = 2;
	SonicWeldInfo[25].anonymous_5 = 0;
	SonicWeldInfo[25].VertexBuffer = 0;
	SonicWeldInfo[25].VertIndexes = Sonic_LowerArmIndices;
	SonicWeldInfo[26].BaseModel = SONIC_OBJECTS[22];
	SonicWeldInfo[26].ModelA = SONIC_OBJECTS[33];
	SonicWeldInfo[26].ModelB = SONIC_OBJECTS[34];
	SonicWeldInfo[26].VertexPairCount = (uint8_t)(LengthOfArray(Sonic_UpperLegIndices) / 2);
	SonicWeldInfo[26].WeldType = 2;
	SonicWeldInfo[26].anonymous_5 = 0;
	SonicWeldInfo[26].VertexBuffer = 0;
	SonicWeldInfo[26].VertIndexes = Sonic_UpperLegIndices;
	SonicWeldInfo[27].BaseModel = SONIC_OBJECTS[22];
	SonicWeldInfo[27].ModelA = SONIC_OBJECTS[34];
	SonicWeldInfo[27].ModelB = SONIC_OBJECTS[35];
	SonicWeldInfo[27].VertexPairCount = (uint8_t)(LengthOfArray(Sonic_LowerLegIndices) / 2);
	SonicWeldInfo[27].WeldType = 2;
	SonicWeldInfo[27].anonymous_5 = 0;
	SonicWeldInfo[27].VertexBuffer = 0;
	SonicWeldInfo[27].VertIndexes = Sonic_LowerLegIndices;
	SonicWeldInfo[28].BaseModel = SONIC_OBJECTS[22];
	SonicWeldInfo[28].ModelA = SONIC_OBJECTS[38];
	v3 = SONIC_OBJECTS[39];
	SonicWeldInfo[28].VertIndexes = Sonic_UpperLegIndices;
	SonicWeldInfo[28].ModelB = v3;
	SonicWeldInfo[28].VertexPairCount = (uint8_t)(LengthOfArray(Sonic_UpperLegIndices) / 2);
	SonicWeldInfo[28].WeldType = 2;
	SonicWeldInfo[28].anonymous_5 = 0;
	SonicWeldInfo[28].VertexBuffer = 0;
	SonicWeldInfo[29].BaseModel = SONIC_OBJECTS[22];
	SonicWeldInfo[29].ModelA = SONIC_OBJECTS[39];
	SonicWeldInfo[29].ModelB = SONIC_OBJECTS[40];
	SonicWeldInfo[29].VertexPairCount = (uint8_t)(LengthOfArray(Sonic_LowerLegIndices) / 2);
	SonicWeldInfo[29].WeldType = 2;
	SonicWeldInfo[29].anonymous_5 = 0;
	SonicWeldInfo[29].VertexBuffer = 0;
	SonicWeldInfo[29].VertIndexes = Sonic_LowerLegIndices;
	SonicWeldInfo[30].BaseModel = SONIC_OBJECTS[22];
	SonicWeldInfo[30].ModelA = SONIC_OBJECTS[36];
	SonicWeldInfo[30].ModelB = SONIC_OBJECTS[37];
	SonicWeldInfo[30].VertexPairCount = (uint8_t)(LengthOfArray(Sonic_ShoeIndices) / 2);
	SonicWeldInfo[30].WeldType = 2;
	SonicWeldInfo[30].anonymous_5 = 0;
	SonicWeldInfo[30].VertexBuffer = 0;
	SonicWeldInfo[30].VertIndexes = Sonic_ShoeIndices;
	SonicWeldInfo[31].BaseModel = SONIC_OBJECTS[22];
	SonicWeldInfo[31].ModelA = SONIC_OBJECTS[41];
	SonicWeldInfo[31].ModelB = SONIC_OBJECTS[42];
	SonicWeldInfo[31].VertexPairCount = (uint8_t)(LengthOfArray(Sonic_ShoeIndices) / 2);
	SonicWeldInfo[31].WeldType = 2;
	SonicWeldInfo[31].anonymous_5 = 0;
	SonicWeldInfo[31].VertexBuffer = 0;
	SonicWeldInfo[31].VertIndexes = Sonic_ShoeIndices;
	SonicWeldInfo[32].BaseModel = SONIC_OBJECTS[22];
	SonicWeldInfo[32].ModelA = SONIC_OBJECTS[31];
	SonicWeldInfo[32].ModelB = SONIC_OBJECTS[32];
	SonicWeldInfo[32].VertexPairCount = (uint8_t)(LengthOfArray(Sonic_HandIndices) / 2);
	SonicWeldInfo[32].WeldType = 2;
	SonicWeldInfo[32].anonymous_5 = 0;
	SonicWeldInfo[32].VertexBuffer = 0;
	SonicWeldInfo[32].VertIndexes = Sonic_HandIndices;
	SonicWeldInfo[33].BaseModel = SONIC_OBJECTS[22];
	SonicWeldInfo[33].ModelA = SONIC_OBJECTS[26];
	v4 = SONIC_OBJECTS[27];
	SonicWeldInfo[33].anonymous_5 = 0;
	SonicWeldInfo[33].VertexBuffer = 0;
	SonicWeldInfo[33].VertIndexes = Sonic_HandIndices;
	SonicWeldInfo[33].ModelB = v4;
	SonicWeldInfo[33].VertexPairCount = (uint8_t)(LengthOfArray(Sonic_HandIndices) / 2);
	SonicWeldInfo[33].WeldType = 2;
	SonicWeldInfo[34].BaseModel = SONIC_OBJECTS[22];
	SonicWeldInfo[34].ModelA = SONIC_OBJECTS[31];
	SonicWeldInfo[34].ModelB = SONIC_OBJECTS[32];
	SonicWeldInfo[34].anonymous_5 = 0;
	SonicWeldInfo[34].VertexBuffer = 0;
	SonicWeldInfo[34].VertexPairCount = 4;
	SonicWeldInfo[34].VertIndexes = Sonic_HandIndices;
	SonicWeldInfo[34].WeldType = 2;
	SonicWeldInfo[35].BaseModel = SONIC_OBJECTS[22];
	SonicWeldInfo[35].ModelA = SONIC_OBJECTS[26];
	v5 = SONIC_OBJECTS[27];
	SonicWeldInfo[35].anonymous_5 = 0;
	SonicWeldInfo[35].VertexBuffer = 0;
	SonicWeldInfo[36].BaseModel = 0;
	SonicWeldInfo[36].ModelA = 0;
	SonicWeldInfo[36].ModelB = 0;
	SonicWeldInfo[35].VertIndexes = Sonic_HandIndices;
	SonicWeldInfo[36].VertexPairCount = 0;
	SonicWeldInfo[36].VertexBuffer = 0;
	SonicWeldInfo[35].VertexPairCount = 4;
	SonicWeldInfo[35].ModelB = v5;
	SonicWeldInfo[35].WeldType = 2;
	SonicWeldInfo[36].VertIndexes = 0;
}

void __cdecl InitNPCSonicWeldInfo_mod()
{
	NJS_OBJECT *v0; // ebp@1
	NJS_OBJECT *v1; // ebp@1
	NJS_OBJECT *v2; // ebp@1
	NJS_OBJECT *v3; // ebp@1
	NJS_OBJECT *v4; // eax@1

	NPCSonicWeldInfo[0].BaseModel = *SONIC_OBJECTS;
	NPCSonicWeldInfo[0].ModelA = SONIC_OBJECTS[1];
	NPCSonicWeldInfo[0].ModelB = SONIC_OBJECTS[2];
	NPCSonicWeldInfo[0].anonymous_5 = 0;
	NPCSonicWeldInfo[0].VertexBuffer = 0;
	NPCSonicWeldInfo[0].VertIndexes = Sonic_UpperArmIndices;
	NPCSonicWeldInfo[0].WeldType = 2;
	NPCSonicWeldInfo[0].VertexPairCount = (uint8_t)(LengthOfArray(Sonic_UpperArmIndices) / 2);
	NPCSonicWeldInfo[1].BaseModel = *SONIC_OBJECTS;
	NPCSonicWeldInfo[1].ModelA = SONIC_OBJECTS[2];
	NPCSonicWeldInfo[1].ModelB = SONIC_OBJECTS[3];
	NPCSonicWeldInfo[1].VertexPairCount = (uint8_t)(LengthOfArray(Sonic_LowerArmIndices) / 2);
	NPCSonicWeldInfo[1].WeldType = 2;
	NPCSonicWeldInfo[1].anonymous_5 = 0;
	NPCSonicWeldInfo[1].VertexBuffer = 0;
	NPCSonicWeldInfo[1].VertIndexes = Sonic_LowerArmIndices;
	NPCSonicWeldInfo[2].BaseModel = *SONIC_OBJECTS;
	NPCSonicWeldInfo[2].ModelA = SONIC_OBJECTS[7];
	NPCSonicWeldInfo[2].ModelB = SONIC_OBJECTS[8];
	NPCSonicWeldInfo[2].VertexPairCount = (uint8_t)(LengthOfArray(Sonic_UpperArmIndices) / 2);
	NPCSonicWeldInfo[2].WeldType = 2;
	NPCSonicWeldInfo[2].anonymous_5 = 0;
	NPCSonicWeldInfo[2].VertexBuffer = 0;
	NPCSonicWeldInfo[2].VertIndexes = Sonic_UpperArmIndices;
	NPCSonicWeldInfo[3].BaseModel = *SONIC_OBJECTS;
	NPCSonicWeldInfo[3].ModelA = SONIC_OBJECTS[8];
	v0 = SONIC_OBJECTS[9];
	NPCSonicWeldInfo[3].VertIndexes = Sonic_LowerArmIndices;
	NPCSonicWeldInfo[3].ModelB = v0;
	NPCSonicWeldInfo[3].VertexPairCount = (uint8_t)(LengthOfArray(Sonic_LowerArmIndices) / 2);
	NPCSonicWeldInfo[3].WeldType = 2;
	NPCSonicWeldInfo[3].anonymous_5 = 0;
	NPCSonicWeldInfo[3].VertexBuffer = 0;
	NPCSonicWeldInfo[4].BaseModel = *SONIC_OBJECTS;
	NPCSonicWeldInfo[4].ModelA = SONIC_OBJECTS[12];
	NPCSonicWeldInfo[4].ModelB = SONIC_OBJECTS[13];
	NPCSonicWeldInfo[4].VertexPairCount = (uint8_t)(LengthOfArray(Sonic_UpperLegIndices) / 2);
	NPCSonicWeldInfo[4].WeldType = 2;
	NPCSonicWeldInfo[4].anonymous_5 = 0;
	NPCSonicWeldInfo[4].VertexBuffer = 0;
	NPCSonicWeldInfo[4].VertIndexes = Sonic_UpperLegIndices;
	NPCSonicWeldInfo[5].BaseModel = *SONIC_OBJECTS;
	NPCSonicWeldInfo[5].ModelA = SONIC_OBJECTS[13];
	NPCSonicWeldInfo[5].ModelB = SONIC_OBJECTS[14];
	NPCSonicWeldInfo[5].VertexPairCount = (uint8_t)(LengthOfArray(Sonic_LowerLegIndices) / 2);
	NPCSonicWeldInfo[5].WeldType = 2;
	NPCSonicWeldInfo[5].anonymous_5 = 0;
	NPCSonicWeldInfo[5].VertexBuffer = 0;
	NPCSonicWeldInfo[5].VertIndexes = Sonic_LowerLegIndices;
	NPCSonicWeldInfo[6].BaseModel = *SONIC_OBJECTS;
	NPCSonicWeldInfo[6].ModelA = SONIC_OBJECTS[17];
	NPCSonicWeldInfo[6].ModelB = SONIC_OBJECTS[18];
	NPCSonicWeldInfo[6].VertexPairCount = (uint8_t)(LengthOfArray(Sonic_UpperLegIndices) / 2);
	NPCSonicWeldInfo[6].WeldType = 2;
	NPCSonicWeldInfo[6].anonymous_5 = 0;
	NPCSonicWeldInfo[6].VertexBuffer = 0;
	NPCSonicWeldInfo[6].VertIndexes = Sonic_UpperLegIndices;
	NPCSonicWeldInfo[7].BaseModel = *SONIC_OBJECTS;
	NPCSonicWeldInfo[7].ModelA = SONIC_OBJECTS[18];
	v1 = SONIC_OBJECTS[19];
	NPCSonicWeldInfo[7].VertIndexes = Sonic_LowerLegIndices;
	NPCSonicWeldInfo[7].ModelB = v1;
	NPCSonicWeldInfo[7].VertexPairCount = (uint8_t)(LengthOfArray(Sonic_LowerLegIndices) / 2);
	NPCSonicWeldInfo[7].WeldType = 2;
	NPCSonicWeldInfo[7].anonymous_5 = 0;
	NPCSonicWeldInfo[7].VertexBuffer = 0;
	NPCSonicWeldInfo[8].BaseModel = *SONIC_OBJECTS;
	NPCSonicWeldInfo[8].ModelA = SONIC_OBJECTS[15];
	NPCSonicWeldInfo[8].ModelB = SONIC_OBJECTS[16];
	NPCSonicWeldInfo[8].VertexPairCount = (uint8_t)(LengthOfArray(Sonic_ShoeIndices) / 2);
	NPCSonicWeldInfo[8].WeldType = 2;
	NPCSonicWeldInfo[8].anonymous_5 = 0;
	NPCSonicWeldInfo[8].VertexBuffer = 0;
	NPCSonicWeldInfo[8].VertIndexes = Sonic_ShoeIndices;
	NPCSonicWeldInfo[9].BaseModel = *SONIC_OBJECTS;
	NPCSonicWeldInfo[9].ModelA = SONIC_OBJECTS[20];
	v2 = SONIC_OBJECTS[21];
	NPCSonicWeldInfo[9].VertIndexes = Sonic_ShoeIndices;
	NPCSonicWeldInfo[9].ModelB = v2;
	NPCSonicWeldInfo[9].VertexPairCount = (uint8_t)(LengthOfArray(Sonic_ShoeIndices) / 2);
	NPCSonicWeldInfo[9].WeldType = 2;
	NPCSonicWeldInfo[9].anonymous_5 = 0;
	NPCSonicWeldInfo[9].VertexBuffer = 0;
	NPCSonicWeldInfo[10].BaseModel = *SONIC_OBJECTS;
	NPCSonicWeldInfo[10].ModelA = SONIC_OBJECTS[10];
	NPCSonicWeldInfo[10].ModelB = SONIC_OBJECTS[11];
	NPCSonicWeldInfo[10].VertexPairCount = (uint8_t)(LengthOfArray(Sonic_HandIndices) / 2);
	NPCSonicWeldInfo[10].WeldType = 2;
	NPCSonicWeldInfo[10].anonymous_5 = 0;
	NPCSonicWeldInfo[10].VertexBuffer = 0;
	NPCSonicWeldInfo[10].VertIndexes = Sonic_HandIndices;
	NPCSonicWeldInfo[11].BaseModel = *SONIC_OBJECTS;
	NPCSonicWeldInfo[11].ModelA = SONIC_OBJECTS[4];
	NPCSonicWeldInfo[11].ModelB = SONIC_OBJECTS[5];
	NPCSonicWeldInfo[11].VertexPairCount = (uint8_t)(LengthOfArray(Sonic_HandIndices) / 2);
	NPCSonicWeldInfo[11].WeldType = 2;
	NPCSonicWeldInfo[11].anonymous_5 = 0;
	NPCSonicWeldInfo[11].VertexBuffer = 0;
	NPCSonicWeldInfo[11].VertIndexes = Sonic_HandIndices;
	NPCSonicWeldInfo[12].BaseModel = *SONIC_OBJECTS;
	NPCSonicWeldInfo[12].ModelA = SONIC_OBJECTS[58];
	NPCSonicWeldInfo[12].ModelB = SONIC_OBJECTS[59];
	NPCSonicWeldInfo[12].VertexPairCount = (uint8_t)(LengthOfArray(Sonic_ShoeIndices) / 2);
	NPCSonicWeldInfo[12].anonymous_5 = 0;
	NPCSonicWeldInfo[12].VertexBuffer = 0;
	NPCSonicWeldInfo[12].WeldType = 2;
	NPCSonicWeldInfo[12].VertIndexes = Sonic_ShoeIndices;
	NPCSonicWeldInfo[13].BaseModel = *SONIC_OBJECTS;
	NPCSonicWeldInfo[13].ModelA = SONIC_OBJECTS[60];
	v3 = SONIC_OBJECTS[61];
	NPCSonicWeldInfo[13].anonymous_5 = 0;
	NPCSonicWeldInfo[13].VertexBuffer = 0;
	NPCSonicWeldInfo[13].ModelB = v3;
	NPCSonicWeldInfo[13].VertIndexes = Sonic_ShoeIndices;
	NPCSonicWeldInfo[13].VertexPairCount = (uint8_t)(LengthOfArray(Sonic_ShoeIndices) / 2);
	NPCSonicWeldInfo[13].WeldType = 2;
	NPCSonicWeldInfo[14].BaseModel = *SONIC_OBJECTS;
	NPCSonicWeldInfo[14].ModelA = SONIC_OBJECTS[2];
	v4 = SONIC_OBJECTS[63];
	NPCSonicWeldInfo[14].anonymous_5 = 0;
	NPCSonicWeldInfo[14].VertexBuffer = 0;
	NPCSonicWeldInfo[15].BaseModel = 0;
	NPCSonicWeldInfo[15].ModelA = 0;
	NPCSonicWeldInfo[15].ModelB = 0;
	NPCSonicWeldInfo[15].VertexPairCount = 0;
	NPCSonicWeldInfo[15].VertexBuffer = 0;
	NPCSonicWeldInfo[14].VertexPairCount = (uint8_t)(LengthOfArray(Sonic_UpperArmIndices) / 2);
	NPCSonicWeldInfo[14].ModelB = v4;
	NPCSonicWeldInfo[14].WeldType = 2;
	NPCSonicWeldInfo[14].VertIndexes = Sonic_UpperArmIndices;
	NPCSonicWeldInfo[15].VertIndexes = 0;
}

void __cdecl InitTailsWeldInfo_mod()
{
	NJS_OBJECT *v0; // ebp@1
	NJS_OBJECT *v1; // ebp@1
	NJS_OBJECT *v2; // ebp@1
	NJS_OBJECT *v3; // edx@1
	NJS_OBJECT *v4; // edx@1
	NJS_OBJECT *v5; // eax@1

	TailsWeldInfo[0].BaseModel = *MILES_OBJECTS;
	TailsWeldInfo[0].ModelA = MILES_OBJECTS[20];
	TailsWeldInfo[0].ModelB = MILES_OBJECTS[21];
	TailsWeldInfo[0].anonymous_5 = 0;
	TailsWeldInfo[0].VertexBuffer = 0;
	TailsWeldInfo[0].VertexPairCount = (uint8_t)(LengthOfArray(Tails_UpperArmIndices) / 2);
	TailsWeldInfo[0].WeldType = 2;
	TailsWeldInfo[0].VertIndexes = Tails_UpperArmIndices;
	TailsWeldInfo[1].BaseModel = *MILES_OBJECTS;
	TailsWeldInfo[1].ModelA = MILES_OBJECTS[21];
	TailsWeldInfo[1].ModelB = MILES_OBJECTS[22];
	TailsWeldInfo[1].VertexPairCount = (uint8_t)(LengthOfArray(Tails_LowerArmIndices) / 2);
	TailsWeldInfo[1].WeldType = 2;
	TailsWeldInfo[1].anonymous_5 = 0;
	TailsWeldInfo[1].VertexBuffer = 0;
	TailsWeldInfo[1].VertIndexes = Tails_LowerArmIndices;
	TailsWeldInfo[2].BaseModel = *MILES_OBJECTS;
	TailsWeldInfo[2].ModelA = MILES_OBJECTS[23];
	v0 = MILES_OBJECTS[24];
	TailsWeldInfo[2].VertIndexes = Tails_UpperArmIndices;
	TailsWeldInfo[2].ModelB = v0;
	TailsWeldInfo[2].VertexPairCount = (uint8_t)(LengthOfArray(Tails_UpperArmIndices) / 2);
	TailsWeldInfo[2].WeldType = 2;
	TailsWeldInfo[2].anonymous_5 = 0;
	TailsWeldInfo[2].VertexBuffer = 0;
	TailsWeldInfo[3].BaseModel = *MILES_OBJECTS;
	TailsWeldInfo[3].ModelA = MILES_OBJECTS[24];
	TailsWeldInfo[3].ModelB = MILES_OBJECTS[25];
	TailsWeldInfo[3].VertexPairCount = (uint8_t)(LengthOfArray(Tails_LowerArmIndices) / 2);
	TailsWeldInfo[3].WeldType = 2;
	TailsWeldInfo[3].anonymous_5 = 0;
	TailsWeldInfo[3].VertexBuffer = 0;
	TailsWeldInfo[3].VertIndexes = Tails_LowerArmIndices;
	TailsWeldInfo[4].BaseModel = *MILES_OBJECTS;
	TailsWeldInfo[4].ModelA = MILES_OBJECTS[26];
	TailsWeldInfo[4].ModelB = MILES_OBJECTS[27];
	TailsWeldInfo[4].VertexPairCount = (uint8_t)(LengthOfArray(Tails_LegIndices) / 2);
	TailsWeldInfo[4].WeldType = 2;
	TailsWeldInfo[4].anonymous_5 = 0;
	TailsWeldInfo[4].VertexBuffer = 0;
	TailsWeldInfo[4].VertIndexes = Tails_LegIndices;
	TailsWeldInfo[5].BaseModel = *MILES_OBJECTS;
	TailsWeldInfo[5].ModelA = MILES_OBJECTS[27];
	TailsWeldInfo[5].ModelB = MILES_OBJECTS[28];
	TailsWeldInfo[5].VertexPairCount = (uint8_t)(LengthOfArray(Tails_LegIndices) / 2);
	TailsWeldInfo[5].WeldType = 2;
	TailsWeldInfo[5].anonymous_5 = 0;
	TailsWeldInfo[5].VertexBuffer = 0;
	TailsWeldInfo[5].VertIndexes = Tails_LegIndices;
	TailsWeldInfo[6].BaseModel = *MILES_OBJECTS;
	TailsWeldInfo[6].ModelA = MILES_OBJECTS[29];
	TailsWeldInfo[6].ModelB = MILES_OBJECTS[30];
	TailsWeldInfo[6].VertexPairCount = (uint8_t)(LengthOfArray(Tails_LegIndices) / 2);
	TailsWeldInfo[6].WeldType = 2;
	TailsWeldInfo[6].anonymous_5 = 0;
	TailsWeldInfo[6].VertexBuffer = 0;
	TailsWeldInfo[6].VertIndexes = Tails_LegIndices;
	TailsWeldInfo[7].BaseModel = *MILES_OBJECTS;
	TailsWeldInfo[7].ModelA = MILES_OBJECTS[30];
	TailsWeldInfo[7].ModelB = MILES_OBJECTS[31];
	TailsWeldInfo[7].VertexPairCount = (uint8_t)(LengthOfArray(Tails_LegIndices) / 2);
	TailsWeldInfo[7].WeldType = 2;
	TailsWeldInfo[7].anonymous_5 = 0;
	TailsWeldInfo[7].VertexBuffer = 0;
	TailsWeldInfo[7].VertIndexes = Tails_LegIndices;
	TailsWeldInfo[8].BaseModel = *MILES_OBJECTS;
	TailsWeldInfo[8].ModelA = MILES_OBJECTS[32];
	TailsWeldInfo[8].ModelB = MILES_OBJECTS[33];
	TailsWeldInfo[8].VertexPairCount = (uint8_t)(LengthOfArray(Tails_ShoeIndices) / 2);
	TailsWeldInfo[8].WeldType = 2;
	TailsWeldInfo[8].anonymous_5 = 0;
	TailsWeldInfo[8].VertexBuffer = 0;
	TailsWeldInfo[8].VertIndexes = Tails_ShoeIndices;
	TailsWeldInfo[9].BaseModel = *MILES_OBJECTS;
	TailsWeldInfo[9].ModelA = MILES_OBJECTS[34];
	v1 = MILES_OBJECTS[35];
	TailsWeldInfo[9].VertIndexes = Tails_ShoeIndices;
	TailsWeldInfo[9].ModelB = v1;
	TailsWeldInfo[9].VertexPairCount = (uint8_t)(LengthOfArray(Tails_ShoeIndices) / 2);
	TailsWeldInfo[9].WeldType = 2;
	TailsWeldInfo[9].anonymous_5 = 0;
	TailsWeldInfo[9].VertexBuffer = 0;
	TailsWeldInfo[10].BaseModel = *MILES_OBJECTS;
	TailsWeldInfo[10].ModelA = MILES_OBJECTS[36];
	TailsWeldInfo[10].ModelB = MILES_OBJECTS[37];
	TailsWeldInfo[10].VertexPairCount = (uint8_t)(LengthOfArray(Tails_HandIndices) / 2);
	TailsWeldInfo[10].WeldType = 2;
	TailsWeldInfo[10].anonymous_5 = 0;
	TailsWeldInfo[10].VertexBuffer = 0;
	TailsWeldInfo[10].VertIndexes = Tails_HandIndices;
	TailsWeldInfo[11].BaseModel = *MILES_OBJECTS;
	TailsWeldInfo[11].ModelA = MILES_OBJECTS[38];
	TailsWeldInfo[11].ModelB = MILES_OBJECTS[39];
	TailsWeldInfo[11].VertexPairCount = (uint8_t)(LengthOfArray(Tails_HandIndices) / 2);
	TailsWeldInfo[11].WeldType = 2;
	TailsWeldInfo[11].anonymous_5 = 0;
	TailsWeldInfo[11].VertexBuffer = 0;
	TailsWeldInfo[11].VertIndexes = Tails_HandIndices;
	TailsWeldInfo[12].BaseModel = MILES_OBJECTS[1];
	TailsWeldInfo[12].ModelA = MILES_OBJECTS[40];
	TailsWeldInfo[12].ModelB = MILES_OBJECTS[41];
	TailsWeldInfo[12].VertexPairCount = (uint8_t)(LengthOfArray(Tails_UpperArmIndices) / 2);
	TailsWeldInfo[12].WeldType = 2;
	TailsWeldInfo[12].anonymous_5 = 0;
	TailsWeldInfo[12].VertexBuffer = 0;
	TailsWeldInfo[12].VertIndexes = Tails_UpperArmIndices;
	TailsWeldInfo[13].BaseModel = MILES_OBJECTS[1];
	TailsWeldInfo[13].ModelA = MILES_OBJECTS[41];
	TailsWeldInfo[13].ModelB = MILES_OBJECTS[42];
	TailsWeldInfo[13].VertexPairCount = (uint8_t)(LengthOfArray(Tails_LowerArmIndices) / 2);
	TailsWeldInfo[13].WeldType = 2;
	TailsWeldInfo[13].anonymous_5 = 0;
	TailsWeldInfo[13].VertexBuffer = 0;
	TailsWeldInfo[13].VertIndexes = Tails_LowerArmIndices;
	TailsWeldInfo[14].BaseModel = MILES_OBJECTS[1];
	TailsWeldInfo[14].ModelA = MILES_OBJECTS[43];
	TailsWeldInfo[14].ModelB = MILES_OBJECTS[44];
	TailsWeldInfo[14].VertexPairCount = (uint8_t)(LengthOfArray(Tails_UpperArmIndices) / 2);
	TailsWeldInfo[14].WeldType = 2;
	TailsWeldInfo[14].anonymous_5 = 0;
	TailsWeldInfo[14].VertexBuffer = 0;
	TailsWeldInfo[14].VertIndexes = Tails_UpperArmIndices;
	TailsWeldInfo[15].BaseModel = MILES_OBJECTS[1];
	TailsWeldInfo[15].ModelA = MILES_OBJECTS[44];
	TailsWeldInfo[15].ModelB = MILES_OBJECTS[45];
	TailsWeldInfo[15].VertexPairCount = (uint8_t)(LengthOfArray(Tails_LowerArmIndices) / 2);
	TailsWeldInfo[15].WeldType = 2;
	TailsWeldInfo[15].anonymous_5 = 0;
	TailsWeldInfo[15].VertexBuffer = 0;
	TailsWeldInfo[15].VertIndexes = Tails_LowerArmIndices;
	TailsWeldInfo[16].BaseModel = MILES_OBJECTS[1];
	TailsWeldInfo[16].ModelA = MILES_OBJECTS[46];
	TailsWeldInfo[16].ModelB = MILES_OBJECTS[47];
	TailsWeldInfo[16].VertexPairCount = (uint8_t)(LengthOfArray(Tails_LegIndices) / 2);
	TailsWeldInfo[16].WeldType = 2;
	TailsWeldInfo[16].anonymous_5 = 0;
	TailsWeldInfo[16].VertexBuffer = 0;
	TailsWeldInfo[16].VertIndexes = Tails_LegIndices;
	TailsWeldInfo[17].BaseModel = MILES_OBJECTS[1];
	TailsWeldInfo[17].ModelA = MILES_OBJECTS[47];
	TailsWeldInfo[17].ModelB = MILES_OBJECTS[48];
	TailsWeldInfo[17].VertexPairCount = (uint8_t)(LengthOfArray(Tails_LegIndices) / 2);
	TailsWeldInfo[17].WeldType = 2;
	TailsWeldInfo[17].anonymous_5 = 0;
	TailsWeldInfo[17].VertexBuffer = 0;
	TailsWeldInfo[17].VertIndexes = Tails_LegIndices;
	TailsWeldInfo[18].BaseModel = MILES_OBJECTS[1];
	TailsWeldInfo[18].ModelA = MILES_OBJECTS[49];
	TailsWeldInfo[18].ModelB = MILES_OBJECTS[50];
	TailsWeldInfo[18].VertexPairCount = (uint8_t)(LengthOfArray(Tails_LegIndices) / 2);
	TailsWeldInfo[18].WeldType = 2;
	TailsWeldInfo[18].anonymous_5 = 0;
	TailsWeldInfo[18].VertexBuffer = 0;
	TailsWeldInfo[18].VertIndexes = Tails_LegIndices;
	TailsWeldInfo[19].BaseModel = MILES_OBJECTS[1];
	TailsWeldInfo[19].ModelA = MILES_OBJECTS[50];
	v2 = MILES_OBJECTS[51];
	TailsWeldInfo[19].VertIndexes = Tails_LegIndices;
	TailsWeldInfo[19].ModelB = v2;
	TailsWeldInfo[19].VertexPairCount = (uint8_t)(LengthOfArray(Tails_LegIndices) / 2);
	TailsWeldInfo[19].WeldType = 2;
	TailsWeldInfo[19].anonymous_5 = 0;
	TailsWeldInfo[19].VertexBuffer = 0;
	TailsWeldInfo[20].BaseModel = MILES_OBJECTS[1];
	TailsWeldInfo[20].ModelA = MILES_OBJECTS[52];
	TailsWeldInfo[20].ModelB = MILES_OBJECTS[53];
	TailsWeldInfo[20].VertexPairCount = (uint8_t)(LengthOfArray(Tails_ShoeIndices) / 2);
	TailsWeldInfo[20].WeldType = 2;
	TailsWeldInfo[20].anonymous_5 = 0;
	TailsWeldInfo[20].VertexBuffer = 0;
	TailsWeldInfo[20].VertIndexes = Tails_ShoeIndices;
	TailsWeldInfo[21].BaseModel = MILES_OBJECTS[1];
	TailsWeldInfo[21].ModelA = MILES_OBJECTS[54];
	TailsWeldInfo[21].ModelB = MILES_OBJECTS[55];
	TailsWeldInfo[21].VertexPairCount = (uint8_t)(LengthOfArray(Tails_ShoeIndices) / 2);
	TailsWeldInfo[21].WeldType = 2;
	TailsWeldInfo[21].anonymous_5 = 0;
	TailsWeldInfo[21].VertexBuffer = 0;
	TailsWeldInfo[21].VertIndexes = Tails_ShoeIndices;
	TailsWeldInfo[22].BaseModel = MILES_OBJECTS[1];
	TailsWeldInfo[22].ModelA = MILES_OBJECTS[56];
	TailsWeldInfo[22].ModelB = MILES_OBJECTS[57];
	TailsWeldInfo[22].VertexPairCount = (uint8_t)(LengthOfArray(Tails_HandIndices) / 2);
	TailsWeldInfo[22].WeldType = 2;
	TailsWeldInfo[22].anonymous_5 = 0;
	TailsWeldInfo[22].VertexBuffer = 0;
	TailsWeldInfo[22].VertIndexes = Tails_HandIndices;
	TailsWeldInfo[23].BaseModel = MILES_OBJECTS[1];
	TailsWeldInfo[23].ModelA = MILES_OBJECTS[58];
	TailsWeldInfo[23].ModelB = MILES_OBJECTS[59];
	TailsWeldInfo[23].VertexPairCount = (uint8_t)(LengthOfArray(Tails_HandIndices) / 2);
	TailsWeldInfo[23].WeldType = 2;
	TailsWeldInfo[23].anonymous_5 = 0;
	TailsWeldInfo[23].VertexBuffer = 0;
	TailsWeldInfo[23].VertIndexes = Tails_HandIndices;
	TailsWeldInfo[24].BaseModel = *MILES_OBJECTS;
	TailsWeldInfo[24].ModelA = MILES_OBJECTS[37];
	TailsWeldInfo[24].ModelB = 0;
	TailsWeldInfo[24].VertexPairCount = 2;
	TailsWeldInfo[24].WeldType = 4;
	TailsWeldInfo[24].anonymous_5 = 0;
	TailsWeldInfo[24].VertexBuffer = 0;
	TailsWeldInfo[24].VertIndexes = 0;
	TailsWeldInfo[25].BaseModel = *MILES_OBJECTS;
	TailsWeldInfo[25].ModelA = MILES_OBJECTS[39];
	TailsWeldInfo[25].ModelB = 0;
	TailsWeldInfo[25].VertexPairCount = 2;
	TailsWeldInfo[25].WeldType = 5;
	TailsWeldInfo[25].anonymous_5 = 0;
	TailsWeldInfo[25].VertexBuffer = 0;
	TailsWeldInfo[25].VertIndexes = 0;
	TailsWeldInfo[26].BaseModel = *MILES_OBJECTS;
	v3 = MILES_OBJECTS[33];
	TailsWeldInfo[26].ModelB = 0;
	TailsWeldInfo[26].VertexPairCount = 0;
	TailsWeldInfo[26].anonymous_5 = 0;
	TailsWeldInfo[26].VertexBuffer = 0;
	TailsWeldInfo[26].VertIndexes = 0;
	TailsWeldInfo[26].ModelA = v3;
	TailsWeldInfo[26].WeldType = 6;
	TailsWeldInfo[27].BaseModel = *MILES_OBJECTS;
	v4 = MILES_OBJECTS[35];
	TailsWeldInfo[27].ModelB = 0;
	TailsWeldInfo[27].VertexPairCount = 0;
	TailsWeldInfo[27].anonymous_5 = 0;
	TailsWeldInfo[27].VertexBuffer = 0;
	TailsWeldInfo[27].VertIndexes = 0;
	TailsWeldInfo[27].ModelA = v4;
	TailsWeldInfo[27].WeldType = 7;
	TailsWeldInfo[28].BaseModel = *MILES_OBJECTS;
	v5 = MILES_OBJECTS[4];
	TailsWeldInfo[28].ModelB = 0;
	TailsWeldInfo[28].VertexPairCount = 0;
	TailsWeldInfo[28].anonymous_5 = 0;
	TailsWeldInfo[28].VertexBuffer = 0;
	TailsWeldInfo[28].VertIndexes = 0;
	TailsWeldInfo[29].BaseModel = 0;
	TailsWeldInfo[29].ModelA = 0;
	TailsWeldInfo[29].ModelB = 0;
	TailsWeldInfo[29].VertexPairCount = 0;
	TailsWeldInfo[29].VertexBuffer = 0;
	TailsWeldInfo[28].ModelA = v5;
	TailsWeldInfo[28].WeldType = 8;
	TailsWeldInfo[29].VertIndexes = 0;
}

void __cdecl InitNPCTailsWeldInfo_mod()
{
	NJS_OBJECT *v0; // ebp@1
	NJS_OBJECT *v1; // ebp@1
	NJS_OBJECT *v2; // ebp@1
	NJS_OBJECT *v3; // ebx@1
	NJS_OBJECT *v4; // esi@1
	NJS_OBJECT *v5; // eax@1

	NPCTailsWeldInfo[0].BaseModel = *MILES_OBJECTS;
	NPCTailsWeldInfo[0].ModelA = MILES_OBJECTS[20];
	NPCTailsWeldInfo[0].ModelB = MILES_OBJECTS[21];
	NPCTailsWeldInfo[0].anonymous_5 = 0;
	NPCTailsWeldInfo[0].VertexBuffer = 0;
	NPCTailsWeldInfo[0].VertexPairCount = (uint8_t)(LengthOfArray(Tails_UpperArmIndices) / 2);
	NPCTailsWeldInfo[0].WeldType = 2;
	NPCTailsWeldInfo[0].VertIndexes = Tails_UpperArmIndices;
	NPCTailsWeldInfo[1].BaseModel = *MILES_OBJECTS;
	NPCTailsWeldInfo[1].ModelA = MILES_OBJECTS[21];
	NPCTailsWeldInfo[1].ModelB = MILES_OBJECTS[22];
	NPCTailsWeldInfo[1].VertexPairCount = (uint8_t)(LengthOfArray(Tails_LowerArmIndices) / 2);
	NPCTailsWeldInfo[1].WeldType = 2;
	NPCTailsWeldInfo[1].anonymous_5 = 0;
	NPCTailsWeldInfo[1].VertexBuffer = 0;
	NPCTailsWeldInfo[1].VertIndexes = Tails_LowerArmIndices;
	NPCTailsWeldInfo[2].BaseModel = *MILES_OBJECTS;
	NPCTailsWeldInfo[2].ModelA = MILES_OBJECTS[23];
	v0 = MILES_OBJECTS[24];
	NPCTailsWeldInfo[2].VertIndexes = Tails_UpperArmIndices;
	NPCTailsWeldInfo[2].ModelB = v0;
	NPCTailsWeldInfo[2].VertexPairCount = (uint8_t)(LengthOfArray(Tails_UpperArmIndices) / 2);
	NPCTailsWeldInfo[2].WeldType = 2;
	NPCTailsWeldInfo[2].anonymous_5 = 0;
	NPCTailsWeldInfo[2].VertexBuffer = 0;
	NPCTailsWeldInfo[3].BaseModel = *MILES_OBJECTS;
	NPCTailsWeldInfo[3].ModelA = MILES_OBJECTS[24];
	NPCTailsWeldInfo[3].ModelB = MILES_OBJECTS[25];
	NPCTailsWeldInfo[3].VertexPairCount = (uint8_t)(LengthOfArray(Tails_LowerArmIndices) / 2);
	NPCTailsWeldInfo[3].WeldType = 2;
	NPCTailsWeldInfo[3].anonymous_5 = 0;
	NPCTailsWeldInfo[3].VertexBuffer = 0;
	NPCTailsWeldInfo[3].VertIndexes = Tails_LowerArmIndices;
	NPCTailsWeldInfo[4].BaseModel = *MILES_OBJECTS;
	NPCTailsWeldInfo[4].ModelA = MILES_OBJECTS[26];
	NPCTailsWeldInfo[4].ModelB = MILES_OBJECTS[27];
	NPCTailsWeldInfo[4].VertexPairCount = (uint8_t)(LengthOfArray(Tails_LegIndices) / 2);
	NPCTailsWeldInfo[4].WeldType = 2;
	NPCTailsWeldInfo[4].anonymous_5 = 0;
	NPCTailsWeldInfo[4].VertexBuffer = 0;
	NPCTailsWeldInfo[4].VertIndexes = Tails_LegIndices;
	NPCTailsWeldInfo[5].BaseModel = *MILES_OBJECTS;
	NPCTailsWeldInfo[5].ModelA = MILES_OBJECTS[27];
	NPCTailsWeldInfo[5].ModelB = MILES_OBJECTS[28];
	NPCTailsWeldInfo[5].VertexPairCount = (uint8_t)(LengthOfArray(Tails_LegIndices) / 2);
	NPCTailsWeldInfo[5].WeldType = 2;
	NPCTailsWeldInfo[5].anonymous_5 = 0;
	NPCTailsWeldInfo[5].VertexBuffer = 0;
	NPCTailsWeldInfo[5].VertIndexes = Tails_LegIndices;
	NPCTailsWeldInfo[6].BaseModel = *MILES_OBJECTS;
	NPCTailsWeldInfo[6].ModelA = MILES_OBJECTS[29];
	NPCTailsWeldInfo[6].ModelB = MILES_OBJECTS[30];
	NPCTailsWeldInfo[6].VertexPairCount = (uint8_t)(LengthOfArray(Tails_LegIndices) / 2);
	NPCTailsWeldInfo[6].WeldType = 2;
	NPCTailsWeldInfo[6].anonymous_5 = 0;
	NPCTailsWeldInfo[6].VertexBuffer = 0;
	NPCTailsWeldInfo[6].VertIndexes = Tails_LegIndices;
	NPCTailsWeldInfo[7].BaseModel = *MILES_OBJECTS;
	NPCTailsWeldInfo[7].ModelA = MILES_OBJECTS[30];
	NPCTailsWeldInfo[7].ModelB = MILES_OBJECTS[31];
	NPCTailsWeldInfo[7].VertexPairCount = (uint8_t)(LengthOfArray(Tails_LegIndices) / 2);
	NPCTailsWeldInfo[7].WeldType = 2;
	NPCTailsWeldInfo[7].anonymous_5 = 0;
	NPCTailsWeldInfo[7].VertexBuffer = 0;
	NPCTailsWeldInfo[7].VertIndexes = Tails_LegIndices;
	NPCTailsWeldInfo[8].BaseModel = *MILES_OBJECTS;
	NPCTailsWeldInfo[8].ModelA = MILES_OBJECTS[32];
	NPCTailsWeldInfo[8].ModelB = MILES_OBJECTS[33];
	NPCTailsWeldInfo[8].VertexPairCount = (uint8_t)(LengthOfArray(Tails_ShoeIndices) / 2);
	NPCTailsWeldInfo[8].WeldType = 2;
	NPCTailsWeldInfo[8].anonymous_5 = 0;
	NPCTailsWeldInfo[8].VertexBuffer = 0;
	NPCTailsWeldInfo[8].VertIndexes = Tails_ShoeIndices;
	NPCTailsWeldInfo[9].BaseModel = *MILES_OBJECTS;
	NPCTailsWeldInfo[9].ModelA = MILES_OBJECTS[34];
	v1 = MILES_OBJECTS[35];
	NPCTailsWeldInfo[9].VertIndexes = Tails_ShoeIndices;
	NPCTailsWeldInfo[9].ModelB = v1;
	NPCTailsWeldInfo[9].VertexPairCount = (uint8_t)(LengthOfArray(Tails_ShoeIndices) / 2);
	NPCTailsWeldInfo[9].WeldType = 2;
	NPCTailsWeldInfo[9].anonymous_5 = 0;
	NPCTailsWeldInfo[9].VertexBuffer = 0;
	NPCTailsWeldInfo[10].BaseModel = *MILES_OBJECTS;
	NPCTailsWeldInfo[10].ModelA = MILES_OBJECTS[36];
	NPCTailsWeldInfo[10].ModelB = MILES_OBJECTS[37];
	NPCTailsWeldInfo[10].VertexPairCount = (uint8_t)(LengthOfArray(Tails_HandIndices) / 2);
	NPCTailsWeldInfo[10].WeldType = 2;
	NPCTailsWeldInfo[10].anonymous_5 = 0;
	NPCTailsWeldInfo[10].VertexBuffer = 0;
	NPCTailsWeldInfo[10].VertIndexes = Tails_HandIndices;
	NPCTailsWeldInfo[11].BaseModel = *MILES_OBJECTS;
	NPCTailsWeldInfo[11].ModelA = MILES_OBJECTS[38];
	NPCTailsWeldInfo[11].ModelB = MILES_OBJECTS[39];
	NPCTailsWeldInfo[11].VertexPairCount = (uint8_t)(LengthOfArray(Tails_HandIndices) / 2);
	NPCTailsWeldInfo[11].WeldType = 2;
	NPCTailsWeldInfo[11].anonymous_5 = 0;
	NPCTailsWeldInfo[11].VertexBuffer = 0;
	NPCTailsWeldInfo[11].VertIndexes = Tails_HandIndices;
	NPCTailsWeldInfo[12].BaseModel = MILES_OBJECTS[1];
	NPCTailsWeldInfo[12].ModelA = MILES_OBJECTS[40];
	NPCTailsWeldInfo[12].ModelB = MILES_OBJECTS[41];
	NPCTailsWeldInfo[12].VertexPairCount = (uint8_t)(LengthOfArray(Tails_UpperArmIndices) / 2);
	NPCTailsWeldInfo[12].WeldType = 2;
	NPCTailsWeldInfo[12].anonymous_5 = 0;
	NPCTailsWeldInfo[12].VertexBuffer = 0;
	NPCTailsWeldInfo[12].VertIndexes = Tails_UpperArmIndices;
	NPCTailsWeldInfo[13].BaseModel = MILES_OBJECTS[1];
	NPCTailsWeldInfo[13].ModelA = MILES_OBJECTS[41];
	NPCTailsWeldInfo[13].ModelB = MILES_OBJECTS[42];
	NPCTailsWeldInfo[13].VertexPairCount = (uint8_t)(LengthOfArray(Tails_LowerArmIndices) / 2);
	NPCTailsWeldInfo[13].WeldType = 2;
	NPCTailsWeldInfo[13].anonymous_5 = 0;
	NPCTailsWeldInfo[13].VertexBuffer = 0;
	NPCTailsWeldInfo[13].VertIndexes = Tails_LowerArmIndices;
	NPCTailsWeldInfo[14].BaseModel = MILES_OBJECTS[1];
	NPCTailsWeldInfo[14].ModelA = MILES_OBJECTS[43];
	NPCTailsWeldInfo[14].ModelB = MILES_OBJECTS[44];
	NPCTailsWeldInfo[14].VertexPairCount = (uint8_t)(LengthOfArray(Tails_UpperArmIndices) / 2);
	NPCTailsWeldInfo[14].WeldType = 2;
	NPCTailsWeldInfo[14].anonymous_5 = 0;
	NPCTailsWeldInfo[14].VertexBuffer = 0;
	NPCTailsWeldInfo[14].VertIndexes = Tails_UpperArmIndices;
	NPCTailsWeldInfo[15].BaseModel = MILES_OBJECTS[1];
	NPCTailsWeldInfo[15].ModelA = MILES_OBJECTS[44];
	NPCTailsWeldInfo[15].ModelB = MILES_OBJECTS[45];
	NPCTailsWeldInfo[15].VertexPairCount = (uint8_t)(LengthOfArray(Tails_LowerArmIndices) / 2);
	NPCTailsWeldInfo[15].WeldType = 2;
	NPCTailsWeldInfo[15].anonymous_5 = 0;
	NPCTailsWeldInfo[15].VertexBuffer = 0;
	NPCTailsWeldInfo[15].VertIndexes = Tails_LowerArmIndices;
	NPCTailsWeldInfo[16].BaseModel = MILES_OBJECTS[1];
	NPCTailsWeldInfo[16].ModelA = MILES_OBJECTS[46];
	NPCTailsWeldInfo[16].ModelB = MILES_OBJECTS[47];
	NPCTailsWeldInfo[16].VertexPairCount = (uint8_t)(LengthOfArray(Tails_LegIndices) / 2);
	NPCTailsWeldInfo[16].WeldType = 2;
	NPCTailsWeldInfo[16].anonymous_5 = 0;
	NPCTailsWeldInfo[16].VertexBuffer = 0;
	NPCTailsWeldInfo[16].VertIndexes = Tails_LegIndices;
	NPCTailsWeldInfo[17].BaseModel = MILES_OBJECTS[1];
	NPCTailsWeldInfo[17].ModelA = MILES_OBJECTS[47];
	NPCTailsWeldInfo[17].ModelB = MILES_OBJECTS[48];
	NPCTailsWeldInfo[17].VertexPairCount = (uint8_t)(LengthOfArray(Tails_LegIndices) / 2);
	NPCTailsWeldInfo[17].WeldType = 2;
	NPCTailsWeldInfo[17].anonymous_5 = 0;
	NPCTailsWeldInfo[17].VertexBuffer = 0;
	NPCTailsWeldInfo[17].VertIndexes = Tails_LegIndices;
	NPCTailsWeldInfo[18].BaseModel = MILES_OBJECTS[1];
	NPCTailsWeldInfo[18].ModelA = MILES_OBJECTS[49];
	NPCTailsWeldInfo[18].ModelB = MILES_OBJECTS[50];
	NPCTailsWeldInfo[18].VertexPairCount = (uint8_t)(LengthOfArray(Tails_LegIndices) / 2);
	NPCTailsWeldInfo[18].WeldType = 2;
	NPCTailsWeldInfo[18].anonymous_5 = 0;
	NPCTailsWeldInfo[18].VertexBuffer = 0;
	NPCTailsWeldInfo[18].VertIndexes = Tails_LegIndices;
	NPCTailsWeldInfo[19].BaseModel = MILES_OBJECTS[1];
	NPCTailsWeldInfo[19].ModelA = MILES_OBJECTS[50];
	v2 = MILES_OBJECTS[51];
	NPCTailsWeldInfo[19].anonymous_5 = 0;
	NPCTailsWeldInfo[19].VertexBuffer = 0;
	NPCTailsWeldInfo[19].VertIndexes = Tails_LegIndices;
	NPCTailsWeldInfo[19].ModelB = v2;
	NPCTailsWeldInfo[19].VertexPairCount = (uint8_t)(LengthOfArray(Tails_LegIndices) / 2);
	NPCTailsWeldInfo[19].WeldType = 2;
	NPCTailsWeldInfo[20].BaseModel = MILES_OBJECTS[1];
	NPCTailsWeldInfo[20].ModelA = MILES_OBJECTS[52];
	NPCTailsWeldInfo[20].ModelB = MILES_OBJECTS[53];
	NPCTailsWeldInfo[20].anonymous_5 = 0;
	NPCTailsWeldInfo[20].VertexBuffer = 0;
	NPCTailsWeldInfo[20].VertexPairCount = (uint8_t)(LengthOfArray(Tails_ShoeIndices) / 2);
	NPCTailsWeldInfo[20].WeldType = 2;
	NPCTailsWeldInfo[20].VertIndexes = Tails_ShoeIndices;
	NPCTailsWeldInfo[21].BaseModel = MILES_OBJECTS[1];
	NPCTailsWeldInfo[21].ModelA = MILES_OBJECTS[54];
	v3 = MILES_OBJECTS[55];
	NPCTailsWeldInfo[21].anonymous_5 = 0;
	NPCTailsWeldInfo[21].VertexBuffer = 0;
	NPCTailsWeldInfo[21].ModelB = v3;
	NPCTailsWeldInfo[21].VertIndexes = Tails_ShoeIndices;
	NPCTailsWeldInfo[21].VertexPairCount = (uint8_t)(LengthOfArray(Tails_ShoeIndices) / 2);
	NPCTailsWeldInfo[21].WeldType = 2;
	NPCTailsWeldInfo[22].BaseModel = MILES_OBJECTS[1];
	NPCTailsWeldInfo[22].ModelA = MILES_OBJECTS[56];
	v4 = MILES_OBJECTS[57];
	NPCTailsWeldInfo[22].anonymous_5 = 0;
	NPCTailsWeldInfo[22].VertexBuffer = 0;
	NPCTailsWeldInfo[22].ModelB = v4;
	NPCTailsWeldInfo[22].VertIndexes = Tails_HandIndices;
	NPCTailsWeldInfo[22].VertexPairCount = (uint8_t)(LengthOfArray(Tails_HandIndices) / 2);
	NPCTailsWeldInfo[22].WeldType = 2;
	NPCTailsWeldInfo[23].BaseModel = MILES_OBJECTS[1];
	NPCTailsWeldInfo[23].ModelA = MILES_OBJECTS[58];
	v5 = MILES_OBJECTS[59];
	NPCTailsWeldInfo[23].anonymous_5 = 0;
	NPCTailsWeldInfo[23].VertexBuffer = 0;
	NPCTailsWeldInfo[24].BaseModel = 0;
	NPCTailsWeldInfo[24].ModelA = 0;
	NPCTailsWeldInfo[23].VertIndexes = Tails_HandIndices;
	NPCTailsWeldInfo[24].ModelB = 0;
	NPCTailsWeldInfo[24].VertexPairCount = 0;
	NPCTailsWeldInfo[24].VertexBuffer = 0;
	NPCTailsWeldInfo[23].ModelB = v5;
	NPCTailsWeldInfo[23].VertexPairCount = (uint8_t)(LengthOfArray(Tails_HandIndices) / 2);
	NPCTailsWeldInfo[23].WeldType = 2;
	NPCTailsWeldInfo[24].VertIndexes = 0;
}

void __cdecl InitKnucklesWeldInfo_mod()
{
	NJS_OBJECT *v0; // ebp@1
	NJS_OBJECT *v1; // ebp@1
	NJS_OBJECT *v2; // ebp@1
	NJS_OBJECT *v3; // edx@1
	NJS_OBJECT *v4; // edx@1
	NJS_OBJECT *v5; // eax@1

	KnucklesWeldInfo[0].BaseModel = *KNUCKLES_OBJECTS;
	KnucklesWeldInfo[0].ModelA = KNUCKLES_OBJECTS[2];
	KnucklesWeldInfo[0].ModelB = KNUCKLES_OBJECTS[3];
	KnucklesWeldInfo[0].anonymous_5 = 0;
	KnucklesWeldInfo[0].VertexBuffer = 0;
	KnucklesWeldInfo[0].VertexPairCount = (uint8_t)(LengthOfArray(Knuckles_UpperArmIndices) / 2);
	KnucklesWeldInfo[0].WeldType = 2;
	KnucklesWeldInfo[0].VertIndexes = Knuckles_UpperArmIndices;
	KnucklesWeldInfo[1].BaseModel = *KNUCKLES_OBJECTS;
	KnucklesWeldInfo[1].ModelA = KNUCKLES_OBJECTS[3];
	KnucklesWeldInfo[1].ModelB = KNUCKLES_OBJECTS[4];
	KnucklesWeldInfo[1].VertexPairCount = (uint8_t)(LengthOfArray(Knuckles_LowerArmIndices) / 2);
	KnucklesWeldInfo[1].WeldType = 2;
	KnucklesWeldInfo[1].anonymous_5 = 0;
	KnucklesWeldInfo[1].VertexBuffer = 0;
	KnucklesWeldInfo[1].VertIndexes = Knuckles_LowerArmIndices;
	KnucklesWeldInfo[2].BaseModel = *KNUCKLES_OBJECTS;
	KnucklesWeldInfo[2].ModelA = KNUCKLES_OBJECTS[6];
	v0 = KNUCKLES_OBJECTS[7];
	KnucklesWeldInfo[2].VertIndexes = Knuckles_UpperArmIndices;
	KnucklesWeldInfo[2].ModelB = v0;
	KnucklesWeldInfo[2].VertexPairCount = (uint8_t)(LengthOfArray(Knuckles_UpperArmIndices) / 2);
	KnucklesWeldInfo[2].WeldType = 2;
	KnucklesWeldInfo[2].anonymous_5 = 0;
	KnucklesWeldInfo[2].VertexBuffer = 0;
	KnucklesWeldInfo[3].BaseModel = *KNUCKLES_OBJECTS;
	KnucklesWeldInfo[3].ModelA = KNUCKLES_OBJECTS[7];
	KnucklesWeldInfo[3].ModelB = KNUCKLES_OBJECTS[8];
	KnucklesWeldInfo[3].VertexPairCount = (uint8_t)(LengthOfArray(Knuckles_LowerArmIndices) / 2);
	KnucklesWeldInfo[3].WeldType = 2;
	KnucklesWeldInfo[3].anonymous_5 = 0;
	KnucklesWeldInfo[3].VertexBuffer = 0;
	KnucklesWeldInfo[3].VertIndexes = Knuckles_LowerArmIndices;
	KnucklesWeldInfo[4].BaseModel = *KNUCKLES_OBJECTS;
	KnucklesWeldInfo[4].ModelA = KNUCKLES_OBJECTS[10];
	KnucklesWeldInfo[4].ModelB = KNUCKLES_OBJECTS[11];
	KnucklesWeldInfo[4].VertexPairCount = (uint8_t)(LengthOfArray(Knuckles_LegIndices) / 2);
	KnucklesWeldInfo[4].WeldType = 2;
	KnucklesWeldInfo[4].anonymous_5 = 0;
	KnucklesWeldInfo[4].VertexBuffer = 0;
	KnucklesWeldInfo[4].VertIndexes = Knuckles_LegIndices;
	KnucklesWeldInfo[5].BaseModel = *KNUCKLES_OBJECTS;
	KnucklesWeldInfo[5].ModelA = KNUCKLES_OBJECTS[11];
	KnucklesWeldInfo[5].ModelB = KNUCKLES_OBJECTS[12];
	KnucklesWeldInfo[5].VertexPairCount = (uint8_t)(LengthOfArray(Knuckles_LegIndices) / 2);
	KnucklesWeldInfo[5].WeldType = 2;
	KnucklesWeldInfo[5].anonymous_5 = 0;
	KnucklesWeldInfo[5].VertexBuffer = 0;
	KnucklesWeldInfo[5].VertIndexes = Knuckles_LegIndices;
	KnucklesWeldInfo[6].BaseModel = *KNUCKLES_OBJECTS;
	KnucklesWeldInfo[6].ModelA = KNUCKLES_OBJECTS[13];
	KnucklesWeldInfo[6].ModelB = KNUCKLES_OBJECTS[14];
	KnucklesWeldInfo[6].VertexPairCount = (uint8_t)(LengthOfArray(Knuckles_LegIndices) / 2);
	KnucklesWeldInfo[6].WeldType = 2;
	KnucklesWeldInfo[6].anonymous_5 = 0;
	KnucklesWeldInfo[6].VertexBuffer = 0;
	KnucklesWeldInfo[6].VertIndexes = Knuckles_LegIndices;
	KnucklesWeldInfo[7].BaseModel = *KNUCKLES_OBJECTS;
	KnucklesWeldInfo[7].ModelA = KNUCKLES_OBJECTS[14];
	KnucklesWeldInfo[7].ModelB = KNUCKLES_OBJECTS[15];
	KnucklesWeldInfo[7].VertexPairCount = (uint8_t)(LengthOfArray(Knuckles_LegIndices) / 2);
	KnucklesWeldInfo[7].WeldType = 2;
	KnucklesWeldInfo[7].anonymous_5 = 0;
	KnucklesWeldInfo[7].VertexBuffer = 0;
	KnucklesWeldInfo[7].VertIndexes = Knuckles_LegIndices;
	KnucklesWeldInfo[8].BaseModel = *KNUCKLES_OBJECTS;
	KnucklesWeldInfo[8].ModelA = KNUCKLES_OBJECTS[16];
	KnucklesWeldInfo[8].ModelB = KNUCKLES_OBJECTS[17];
	KnucklesWeldInfo[8].VertexPairCount = (uint8_t)(LengthOfArray(Knuckles_ShoeIndices) / 2);
	KnucklesWeldInfo[8].WeldType = 2;
	KnucklesWeldInfo[8].anonymous_5 = 0;
	KnucklesWeldInfo[8].VertexBuffer = 0;
	KnucklesWeldInfo[8].VertIndexes = Knuckles_ShoeIndices;
	KnucklesWeldInfo[9].BaseModel = *KNUCKLES_OBJECTS;
	KnucklesWeldInfo[9].ModelA = KNUCKLES_OBJECTS[18];
	v1 = KNUCKLES_OBJECTS[19];
	KnucklesWeldInfo[9].VertIndexes = Knuckles_ShoeIndices;
	KnucklesWeldInfo[9].ModelB = v1;
	KnucklesWeldInfo[9].VertexPairCount = (uint8_t)(LengthOfArray(Knuckles_ShoeIndices) / 2);
	KnucklesWeldInfo[9].WeldType = 2;
	KnucklesWeldInfo[9].anonymous_5 = 0;
	KnucklesWeldInfo[9].VertexBuffer = 0;
	KnucklesWeldInfo[10].BaseModel = *KNUCKLES_OBJECTS;
	KnucklesWeldInfo[10].ModelA = KNUCKLES_OBJECTS[20];
	KnucklesWeldInfo[10].ModelB = KNUCKLES_OBJECTS[5];
	KnucklesWeldInfo[10].VertexPairCount = (uint8_t)(LengthOfArray(Knuckles_HandIndices) / 2);
	KnucklesWeldInfo[10].WeldType = 2;
	KnucklesWeldInfo[10].anonymous_5 = 0;
	KnucklesWeldInfo[10].VertexBuffer = 0;
	KnucklesWeldInfo[10].VertIndexes = Knuckles_HandIndices;
	KnucklesWeldInfo[11].BaseModel = *KNUCKLES_OBJECTS;
	KnucklesWeldInfo[11].ModelA = KNUCKLES_OBJECTS[22];
	KnucklesWeldInfo[11].ModelB = KNUCKLES_OBJECTS[9];
	KnucklesWeldInfo[11].VertexPairCount = (uint8_t)(LengthOfArray(Knuckles_HandIndices) / 2);
	KnucklesWeldInfo[11].WeldType = 2;
	KnucklesWeldInfo[11].anonymous_5 = 0;
	KnucklesWeldInfo[11].VertexBuffer = 0;
	KnucklesWeldInfo[11].VertIndexes = Knuckles_HandIndices;
	KnucklesWeldInfo[12].BaseModel = KNUCKLES_OBJECTS[1];
	KnucklesWeldInfo[12].ModelA = KNUCKLES_OBJECTS[24];
	KnucklesWeldInfo[12].ModelB = KNUCKLES_OBJECTS[25];
	KnucklesWeldInfo[12].VertexPairCount = (uint8_t)(LengthOfArray(Knuckles_UpperArmIndices) / 2);
	KnucklesWeldInfo[12].WeldType = 2;
	KnucklesWeldInfo[12].anonymous_5 = 0;
	KnucklesWeldInfo[12].VertexBuffer = 0;
	KnucklesWeldInfo[12].VertIndexes = Knuckles_UpperArmIndices;
	KnucklesWeldInfo[13].BaseModel = KNUCKLES_OBJECTS[1];
	KnucklesWeldInfo[13].ModelA = KNUCKLES_OBJECTS[25];
	KnucklesWeldInfo[13].ModelB = KNUCKLES_OBJECTS[26];
	KnucklesWeldInfo[13].VertexPairCount = (uint8_t)(LengthOfArray(Knuckles_LowerArmIndices) / 2);
	KnucklesWeldInfo[13].WeldType = 2;
	KnucklesWeldInfo[13].anonymous_5 = 0;
	KnucklesWeldInfo[13].VertexBuffer = 0;
	KnucklesWeldInfo[13].VertIndexes = Knuckles_LowerArmIndices;
	KnucklesWeldInfo[14].BaseModel = KNUCKLES_OBJECTS[1];
	KnucklesWeldInfo[14].ModelA = KNUCKLES_OBJECTS[28];
	KnucklesWeldInfo[14].ModelB = KNUCKLES_OBJECTS[29];
	KnucklesWeldInfo[14].VertexPairCount = (uint8_t)(LengthOfArray(Knuckles_UpperArmIndices) / 2);
	KnucklesWeldInfo[14].WeldType = 2;
	KnucklesWeldInfo[14].anonymous_5 = 0;
	KnucklesWeldInfo[14].VertexBuffer = 0;
	KnucklesWeldInfo[14].VertIndexes = Knuckles_UpperArmIndices;
	KnucklesWeldInfo[15].BaseModel = KNUCKLES_OBJECTS[1];
	KnucklesWeldInfo[15].ModelA = KNUCKLES_OBJECTS[29];
	KnucklesWeldInfo[15].ModelB = KNUCKLES_OBJECTS[30];
	KnucklesWeldInfo[15].VertexPairCount = (uint8_t)(LengthOfArray(Knuckles_LowerArmIndices) / 2);
	KnucklesWeldInfo[15].WeldType = 2;
	KnucklesWeldInfo[15].anonymous_5 = 0;
	KnucklesWeldInfo[15].VertexBuffer = 0;
	KnucklesWeldInfo[15].VertIndexes = Knuckles_LowerArmIndices;
	KnucklesWeldInfo[16].BaseModel = KNUCKLES_OBJECTS[1];
	KnucklesWeldInfo[16].ModelA = KNUCKLES_OBJECTS[32];
	KnucklesWeldInfo[16].ModelB = KNUCKLES_OBJECTS[33];
	KnucklesWeldInfo[16].VertexPairCount = (uint8_t)(LengthOfArray(Knuckles_LegIndices) / 2);
	KnucklesWeldInfo[16].WeldType = 2;
	KnucklesWeldInfo[16].anonymous_5 = 0;
	KnucklesWeldInfo[16].VertexBuffer = 0;
	KnucklesWeldInfo[16].VertIndexes = Knuckles_LegIndices;
	KnucklesWeldInfo[17].BaseModel = KNUCKLES_OBJECTS[1];
	KnucklesWeldInfo[17].ModelA = KNUCKLES_OBJECTS[33];
	KnucklesWeldInfo[17].ModelB = KNUCKLES_OBJECTS[34];
	KnucklesWeldInfo[17].VertexPairCount = (uint8_t)(LengthOfArray(Knuckles_LegIndices) / 2);
	KnucklesWeldInfo[17].WeldType = 2;
	KnucklesWeldInfo[17].anonymous_5 = 0;
	KnucklesWeldInfo[17].VertexBuffer = 0;
	KnucklesWeldInfo[17].VertIndexes = Knuckles_LegIndices;
	KnucklesWeldInfo[18].BaseModel = KNUCKLES_OBJECTS[1];
	KnucklesWeldInfo[18].ModelA = KNUCKLES_OBJECTS[35];
	KnucklesWeldInfo[18].ModelB = KNUCKLES_OBJECTS[36];
	KnucklesWeldInfo[18].VertexPairCount = (uint8_t)(LengthOfArray(Knuckles_LegIndices) / 2);
	KnucklesWeldInfo[18].WeldType = 2;
	KnucklesWeldInfo[18].anonymous_5 = 0;
	KnucklesWeldInfo[18].VertexBuffer = 0;
	KnucklesWeldInfo[18].VertIndexes = Knuckles_LegIndices;
	KnucklesWeldInfo[19].BaseModel = KNUCKLES_OBJECTS[1];
	KnucklesWeldInfo[19].ModelA = KNUCKLES_OBJECTS[36];
	v2 = KNUCKLES_OBJECTS[37];
	KnucklesWeldInfo[19].VertIndexes = Knuckles_LegIndices;
	KnucklesWeldInfo[19].ModelB = v2;
	KnucklesWeldInfo[19].VertexPairCount = (uint8_t)(LengthOfArray(Knuckles_LegIndices) / 2);
	KnucklesWeldInfo[19].WeldType = 2;
	KnucklesWeldInfo[19].anonymous_5 = 0;
	KnucklesWeldInfo[19].VertexBuffer = 0;
	KnucklesWeldInfo[20].BaseModel = KNUCKLES_OBJECTS[1];
	KnucklesWeldInfo[20].ModelA = KNUCKLES_OBJECTS[38];
	KnucklesWeldInfo[20].ModelB = KNUCKLES_OBJECTS[39];
	KnucklesWeldInfo[20].VertexPairCount = (uint8_t)(LengthOfArray(Knuckles_ShoeIndices) / 2);
	KnucklesWeldInfo[20].WeldType = 2;
	KnucklesWeldInfo[20].anonymous_5 = 0;
	KnucklesWeldInfo[20].VertexBuffer = 0;
	KnucklesWeldInfo[20].VertIndexes = Knuckles_ShoeIndices;
	KnucklesWeldInfo[21].BaseModel = KNUCKLES_OBJECTS[1];
	KnucklesWeldInfo[21].ModelA = KNUCKLES_OBJECTS[40];
	KnucklesWeldInfo[21].ModelB = KNUCKLES_OBJECTS[41];
	KnucklesWeldInfo[21].VertexPairCount = (uint8_t)(LengthOfArray(Knuckles_ShoeIndices) / 2);
	KnucklesWeldInfo[21].WeldType = 2;
	KnucklesWeldInfo[21].anonymous_5 = 0;
	KnucklesWeldInfo[21].VertexBuffer = 0;
	KnucklesWeldInfo[21].VertIndexes = Knuckles_ShoeIndices;
	KnucklesWeldInfo[22].BaseModel = KNUCKLES_OBJECTS[1];
	KnucklesWeldInfo[22].ModelA = KNUCKLES_OBJECTS[42];
	KnucklesWeldInfo[22].ModelB = KNUCKLES_OBJECTS[27];
	KnucklesWeldInfo[22].VertexPairCount = (uint8_t)(LengthOfArray(Knuckles_HandIndices) / 2);
	KnucklesWeldInfo[22].WeldType = 2;
	KnucklesWeldInfo[22].anonymous_5 = 0;
	KnucklesWeldInfo[22].VertexBuffer = 0;
	KnucklesWeldInfo[22].VertIndexes = Knuckles_HandIndices;
	KnucklesWeldInfo[23].BaseModel = KNUCKLES_OBJECTS[1];
	KnucklesWeldInfo[23].ModelA = KNUCKLES_OBJECTS[44];
	KnucklesWeldInfo[23].ModelB = KNUCKLES_OBJECTS[31];
	KnucklesWeldInfo[23].VertexPairCount = (uint8_t)(LengthOfArray(Knuckles_HandIndices) / 2);
	KnucklesWeldInfo[23].WeldType = 2;
	KnucklesWeldInfo[23].anonymous_5 = 0;
	KnucklesWeldInfo[23].VertexBuffer = 0;
	KnucklesWeldInfo[23].VertIndexes = Knuckles_HandIndices;
	KnucklesWeldInfo[24].BaseModel = *KNUCKLES_OBJECTS;
	KnucklesWeldInfo[24].ModelA = KNUCKLES_OBJECTS[5];
	KnucklesWeldInfo[24].ModelB = 0;
	KnucklesWeldInfo[24].VertexPairCount = 2;
	KnucklesWeldInfo[24].WeldType = 4;
	KnucklesWeldInfo[24].anonymous_5 = 0;
	KnucklesWeldInfo[24].VertexBuffer = 0;
	KnucklesWeldInfo[24].VertIndexes = 0;
	KnucklesWeldInfo[25].BaseModel = *KNUCKLES_OBJECTS;
	KnucklesWeldInfo[25].ModelA = KNUCKLES_OBJECTS[9];
	KnucklesWeldInfo[25].ModelB = 0;
	KnucklesWeldInfo[25].VertexPairCount = 2;
	KnucklesWeldInfo[25].WeldType = 5;
	KnucklesWeldInfo[25].anonymous_5 = 0;
	KnucklesWeldInfo[25].VertexBuffer = 0;
	KnucklesWeldInfo[25].VertIndexes = 0;
	KnucklesWeldInfo[26].BaseModel = *KNUCKLES_OBJECTS;
	v3 = KNUCKLES_OBJECTS[17];
	KnucklesWeldInfo[26].ModelB = 0;
	KnucklesWeldInfo[26].VertexPairCount = 0;
	KnucklesWeldInfo[26].anonymous_5 = 0;
	KnucklesWeldInfo[26].VertexBuffer = 0;
	KnucklesWeldInfo[26].VertIndexes = 0;
	KnucklesWeldInfo[26].ModelA = v3;
	KnucklesWeldInfo[26].WeldType = 6;
	KnucklesWeldInfo[27].BaseModel = *KNUCKLES_OBJECTS;
	v4 = KNUCKLES_OBJECTS[19];
	KnucklesWeldInfo[27].ModelB = 0;
	KnucklesWeldInfo[27].VertexPairCount = 0;
	KnucklesWeldInfo[27].anonymous_5 = 0;
	KnucklesWeldInfo[27].VertexBuffer = 0;
	KnucklesWeldInfo[27].VertIndexes = 0;
	KnucklesWeldInfo[27].ModelA = v4;
	KnucklesWeldInfo[27].WeldType = 7;
	KnucklesWeldInfo[28].BaseModel = *KNUCKLES_OBJECTS;
	v5 = KNUCKLES_OBJECTS[54];
	KnucklesWeldInfo[28].ModelB = 0;
	KnucklesWeldInfo[28].VertexPairCount = 0;
	KnucklesWeldInfo[28].anonymous_5 = 0;
	KnucklesWeldInfo[28].VertexBuffer = 0;
	KnucklesWeldInfo[28].VertIndexes = 0;
	KnucklesWeldInfo[29].BaseModel = 0;
	KnucklesWeldInfo[29].ModelA = 0;
	KnucklesWeldInfo[29].ModelB = 0;
	KnucklesWeldInfo[29].VertexPairCount = 0;
	KnucklesWeldInfo[29].VertexBuffer = 0;
	KnucklesWeldInfo[28].ModelA = v5;
	KnucklesWeldInfo[28].WeldType = 8;
	KnucklesWeldInfo[29].VertIndexes = 0;
}

void __cdecl InitNPCKnucklesWeldInfo_mod()
{
	NJS_OBJECT *v0; // ebp@1
	NJS_OBJECT *v1; // ebp@1
	NJS_OBJECT *v2; // ebp@1
	NJS_OBJECT *v3; // ebx@1
	NJS_OBJECT *v4; // esi@1
	NJS_OBJECT *v5; // eax@1

	NPCKnucklesWeldInfo[0].BaseModel = *KNUCKLES_OBJECTS;
	NPCKnucklesWeldInfo[0].ModelA = KNUCKLES_OBJECTS[2];
	NPCKnucklesWeldInfo[0].ModelB = KNUCKLES_OBJECTS[3];
	NPCKnucklesWeldInfo[0].anonymous_5 = 0;
	NPCKnucklesWeldInfo[0].VertexBuffer = 0;
	NPCKnucklesWeldInfo[0].VertexPairCount = (uint8_t)(LengthOfArray(Knuckles_UpperArmIndices) / 2);
	NPCKnucklesWeldInfo[0].WeldType = 2;
	NPCKnucklesWeldInfo[0].VertIndexes = Knuckles_UpperArmIndices;
	NPCKnucklesWeldInfo[1].BaseModel = *KNUCKLES_OBJECTS;
	NPCKnucklesWeldInfo[1].ModelA = KNUCKLES_OBJECTS[3];
	NPCKnucklesWeldInfo[1].ModelB = KNUCKLES_OBJECTS[4];
	NPCKnucklesWeldInfo[1].VertexPairCount = (uint8_t)(LengthOfArray(Knuckles_LowerArmIndices) / 2);
	NPCKnucklesWeldInfo[1].WeldType = 2;
	NPCKnucklesWeldInfo[1].anonymous_5 = 0;
	NPCKnucklesWeldInfo[1].VertexBuffer = 0;
	NPCKnucklesWeldInfo[1].VertIndexes = Knuckles_LowerArmIndices;
	NPCKnucklesWeldInfo[2].BaseModel = *KNUCKLES_OBJECTS;
	NPCKnucklesWeldInfo[2].ModelA = KNUCKLES_OBJECTS[6];
	v0 = KNUCKLES_OBJECTS[7];
	NPCKnucklesWeldInfo[2].VertIndexes = Knuckles_UpperArmIndices;
	NPCKnucklesWeldInfo[2].ModelB = v0;
	NPCKnucklesWeldInfo[2].VertexPairCount = (uint8_t)(LengthOfArray(Knuckles_UpperArmIndices) / 2);
	NPCKnucklesWeldInfo[2].WeldType = 2;
	NPCKnucklesWeldInfo[2].anonymous_5 = 0;
	NPCKnucklesWeldInfo[2].VertexBuffer = 0;
	NPCKnucklesWeldInfo[3].BaseModel = *KNUCKLES_OBJECTS;
	NPCKnucklesWeldInfo[3].ModelA = KNUCKLES_OBJECTS[7];
	NPCKnucklesWeldInfo[3].ModelB = KNUCKLES_OBJECTS[8];
	NPCKnucklesWeldInfo[3].VertexPairCount = (uint8_t)(LengthOfArray(Knuckles_LowerArmIndices) / 2);
	NPCKnucklesWeldInfo[3].WeldType = 2;
	NPCKnucklesWeldInfo[3].anonymous_5 = 0;
	NPCKnucklesWeldInfo[3].VertexBuffer = 0;
	NPCKnucklesWeldInfo[3].VertIndexes = Knuckles_LowerArmIndices;
	NPCKnucklesWeldInfo[4].BaseModel = *KNUCKLES_OBJECTS;
	NPCKnucklesWeldInfo[4].ModelA = KNUCKLES_OBJECTS[10];
	NPCKnucklesWeldInfo[4].ModelB = KNUCKLES_OBJECTS[11];
	NPCKnucklesWeldInfo[4].VertexPairCount = (uint8_t)(LengthOfArray(Knuckles_LegIndices) / 2);
	NPCKnucklesWeldInfo[4].WeldType = 2;
	NPCKnucklesWeldInfo[4].anonymous_5 = 0;
	NPCKnucklesWeldInfo[4].VertexBuffer = 0;
	NPCKnucklesWeldInfo[4].VertIndexes = Knuckles_LegIndices;
	NPCKnucklesWeldInfo[5].BaseModel = *KNUCKLES_OBJECTS;
	NPCKnucklesWeldInfo[5].ModelA = KNUCKLES_OBJECTS[11];
	NPCKnucklesWeldInfo[5].ModelB = KNUCKLES_OBJECTS[12];
	NPCKnucklesWeldInfo[5].VertexPairCount = (uint8_t)(LengthOfArray(Knuckles_LegIndices) / 2);
	NPCKnucklesWeldInfo[5].WeldType = 2;
	NPCKnucklesWeldInfo[5].anonymous_5 = 0;
	NPCKnucklesWeldInfo[5].VertexBuffer = 0;
	NPCKnucklesWeldInfo[5].VertIndexes = Knuckles_LegIndices;
	NPCKnucklesWeldInfo[6].BaseModel = *KNUCKLES_OBJECTS;
	NPCKnucklesWeldInfo[6].ModelA = KNUCKLES_OBJECTS[13];
	NPCKnucklesWeldInfo[6].ModelB = KNUCKLES_OBJECTS[14];
	NPCKnucklesWeldInfo[6].VertexPairCount = (uint8_t)(LengthOfArray(Knuckles_LegIndices) / 2);
	NPCKnucklesWeldInfo[6].WeldType = 2;
	NPCKnucklesWeldInfo[6].anonymous_5 = 0;
	NPCKnucklesWeldInfo[6].VertexBuffer = 0;
	NPCKnucklesWeldInfo[6].VertIndexes = Knuckles_LegIndices;
	NPCKnucklesWeldInfo[7].BaseModel = *KNUCKLES_OBJECTS;
	NPCKnucklesWeldInfo[7].ModelA = KNUCKLES_OBJECTS[14];
	NPCKnucklesWeldInfo[7].ModelB = KNUCKLES_OBJECTS[15];
	NPCKnucklesWeldInfo[7].VertexPairCount = (uint8_t)(LengthOfArray(Knuckles_LegIndices) / 2);
	NPCKnucklesWeldInfo[7].WeldType = 2;
	NPCKnucklesWeldInfo[7].anonymous_5 = 0;
	NPCKnucklesWeldInfo[7].VertexBuffer = 0;
	NPCKnucklesWeldInfo[7].VertIndexes = Knuckles_LegIndices;
	NPCKnucklesWeldInfo[8].BaseModel = *KNUCKLES_OBJECTS;
	NPCKnucklesWeldInfo[8].ModelA = KNUCKLES_OBJECTS[16];
	NPCKnucklesWeldInfo[8].ModelB = KNUCKLES_OBJECTS[17];
	NPCKnucklesWeldInfo[8].VertexPairCount = (uint8_t)(LengthOfArray(Knuckles_ShoeIndices) / 2);
	NPCKnucklesWeldInfo[8].WeldType = 2;
	NPCKnucklesWeldInfo[8].anonymous_5 = 0;
	NPCKnucklesWeldInfo[8].VertexBuffer = 0;
	NPCKnucklesWeldInfo[8].VertIndexes = Knuckles_ShoeIndices;
	NPCKnucklesWeldInfo[9].BaseModel = *KNUCKLES_OBJECTS;
	NPCKnucklesWeldInfo[9].ModelA = KNUCKLES_OBJECTS[18];
	v1 = KNUCKLES_OBJECTS[19];
	NPCKnucklesWeldInfo[9].VertIndexes = Knuckles_ShoeIndices;
	NPCKnucklesWeldInfo[9].ModelB = v1;
	NPCKnucklesWeldInfo[9].VertexPairCount = (uint8_t)(LengthOfArray(Knuckles_ShoeIndices) / 2);
	NPCKnucklesWeldInfo[9].WeldType = 2;
	NPCKnucklesWeldInfo[9].anonymous_5 = 0;
	NPCKnucklesWeldInfo[9].VertexBuffer = 0;
	NPCKnucklesWeldInfo[10].BaseModel = *KNUCKLES_OBJECTS;
	NPCKnucklesWeldInfo[10].ModelA = KNUCKLES_OBJECTS[20];
	NPCKnucklesWeldInfo[10].ModelB = KNUCKLES_OBJECTS[5];
	NPCKnucklesWeldInfo[10].VertexPairCount = (uint8_t)(LengthOfArray(Knuckles_HandIndices) / 2);
	NPCKnucklesWeldInfo[10].WeldType = 2;
	NPCKnucklesWeldInfo[10].anonymous_5 = 0;
	NPCKnucklesWeldInfo[10].VertexBuffer = 0;
	NPCKnucklesWeldInfo[10].VertIndexes = Knuckles_HandIndices;
	NPCKnucklesWeldInfo[11].BaseModel = *KNUCKLES_OBJECTS;
	NPCKnucklesWeldInfo[11].ModelA = KNUCKLES_OBJECTS[22];
	NPCKnucklesWeldInfo[11].ModelB = KNUCKLES_OBJECTS[9];
	NPCKnucklesWeldInfo[11].VertexPairCount = (uint8_t)(LengthOfArray(Knuckles_HandIndices) / 2);
	NPCKnucklesWeldInfo[11].WeldType = 2;
	NPCKnucklesWeldInfo[11].anonymous_5 = 0;
	NPCKnucklesWeldInfo[11].VertexBuffer = 0;
	NPCKnucklesWeldInfo[11].VertIndexes = Knuckles_HandIndices;
	NPCKnucklesWeldInfo[12].BaseModel = KNUCKLES_OBJECTS[1];
	NPCKnucklesWeldInfo[12].ModelA = KNUCKLES_OBJECTS[24];
	NPCKnucklesWeldInfo[12].ModelB = KNUCKLES_OBJECTS[25];
	NPCKnucklesWeldInfo[12].VertexPairCount = (uint8_t)(LengthOfArray(Knuckles_UpperArmIndices) / 2);
	NPCKnucklesWeldInfo[12].WeldType = 2;
	NPCKnucklesWeldInfo[12].anonymous_5 = 0;
	NPCKnucklesWeldInfo[12].VertexBuffer = 0;
	NPCKnucklesWeldInfo[12].VertIndexes = Knuckles_UpperArmIndices;
	NPCKnucklesWeldInfo[13].BaseModel = KNUCKLES_OBJECTS[1];
	NPCKnucklesWeldInfo[13].ModelA = KNUCKLES_OBJECTS[25];
	NPCKnucklesWeldInfo[13].ModelB = KNUCKLES_OBJECTS[26];
	NPCKnucklesWeldInfo[13].VertexPairCount = (uint8_t)(LengthOfArray(Knuckles_LowerArmIndices) / 2);
	NPCKnucklesWeldInfo[13].WeldType = 2;
	NPCKnucklesWeldInfo[13].anonymous_5 = 0;
	NPCKnucklesWeldInfo[13].VertexBuffer = 0;
	NPCKnucklesWeldInfo[13].VertIndexes = Knuckles_LowerArmIndices;
	NPCKnucklesWeldInfo[14].BaseModel = KNUCKLES_OBJECTS[1];
	NPCKnucklesWeldInfo[14].ModelA = KNUCKLES_OBJECTS[28];
	NPCKnucklesWeldInfo[14].ModelB = KNUCKLES_OBJECTS[29];
	NPCKnucklesWeldInfo[14].VertexPairCount = (uint8_t)(LengthOfArray(Knuckles_UpperArmIndices) / 2);
	NPCKnucklesWeldInfo[14].WeldType = 2;
	NPCKnucklesWeldInfo[14].anonymous_5 = 0;
	NPCKnucklesWeldInfo[14].VertexBuffer = 0;
	NPCKnucklesWeldInfo[14].VertIndexes = Knuckles_UpperArmIndices;
	NPCKnucklesWeldInfo[15].BaseModel = KNUCKLES_OBJECTS[1];
	NPCKnucklesWeldInfo[15].ModelA = KNUCKLES_OBJECTS[29];
	NPCKnucklesWeldInfo[15].ModelB = KNUCKLES_OBJECTS[30];
	NPCKnucklesWeldInfo[15].VertexPairCount = (uint8_t)(LengthOfArray(Knuckles_LowerArmIndices) / 2);
	NPCKnucklesWeldInfo[15].WeldType = 2;
	NPCKnucklesWeldInfo[15].anonymous_5 = 0;
	NPCKnucklesWeldInfo[15].VertexBuffer = 0;
	NPCKnucklesWeldInfo[15].VertIndexes = Knuckles_LowerArmIndices;
	NPCKnucklesWeldInfo[16].BaseModel = KNUCKLES_OBJECTS[1];
	NPCKnucklesWeldInfo[16].ModelA = KNUCKLES_OBJECTS[32];
	NPCKnucklesWeldInfo[16].ModelB = KNUCKLES_OBJECTS[33];
	NPCKnucklesWeldInfo[16].VertexPairCount = (uint8_t)(LengthOfArray(Knuckles_LegIndices) / 2);
	NPCKnucklesWeldInfo[16].WeldType = 2;
	NPCKnucklesWeldInfo[16].anonymous_5 = 0;
	NPCKnucklesWeldInfo[16].VertexBuffer = 0;
	NPCKnucklesWeldInfo[16].VertIndexes = Knuckles_LegIndices;
	NPCKnucklesWeldInfo[17].BaseModel = KNUCKLES_OBJECTS[1];
	NPCKnucklesWeldInfo[17].ModelA = KNUCKLES_OBJECTS[33];
	NPCKnucklesWeldInfo[17].ModelB = KNUCKLES_OBJECTS[34];
	NPCKnucklesWeldInfo[17].VertexPairCount = (uint8_t)(LengthOfArray(Knuckles_LegIndices) / 2);
	NPCKnucklesWeldInfo[17].WeldType = 2;
	NPCKnucklesWeldInfo[17].anonymous_5 = 0;
	NPCKnucklesWeldInfo[17].VertexBuffer = 0;
	NPCKnucklesWeldInfo[17].VertIndexes = Knuckles_LegIndices;
	NPCKnucklesWeldInfo[18].BaseModel = KNUCKLES_OBJECTS[1];
	NPCKnucklesWeldInfo[18].ModelA = KNUCKLES_OBJECTS[35];
	NPCKnucklesWeldInfo[18].ModelB = KNUCKLES_OBJECTS[36];
	NPCKnucklesWeldInfo[18].VertexPairCount = (uint8_t)(LengthOfArray(Knuckles_LegIndices) / 2);
	NPCKnucklesWeldInfo[18].WeldType = 2;
	NPCKnucklesWeldInfo[18].anonymous_5 = 0;
	NPCKnucklesWeldInfo[18].VertexBuffer = 0;
	NPCKnucklesWeldInfo[18].VertIndexes = Knuckles_LegIndices;
	NPCKnucklesWeldInfo[19].BaseModel = KNUCKLES_OBJECTS[1];
	NPCKnucklesWeldInfo[19].ModelA = KNUCKLES_OBJECTS[36];
	v2 = KNUCKLES_OBJECTS[37];
	NPCKnucklesWeldInfo[19].anonymous_5 = 0;
	NPCKnucklesWeldInfo[19].VertexBuffer = 0;
	NPCKnucklesWeldInfo[19].VertIndexes = Knuckles_LegIndices;
	NPCKnucklesWeldInfo[19].ModelB = v2;
	NPCKnucklesWeldInfo[19].VertexPairCount = (uint8_t)(LengthOfArray(Knuckles_LegIndices) / 2);
	NPCKnucklesWeldInfo[19].WeldType = 2;
	NPCKnucklesWeldInfo[20].BaseModel = KNUCKLES_OBJECTS[1];
	NPCKnucklesWeldInfo[20].ModelA = KNUCKLES_OBJECTS[38];
	NPCKnucklesWeldInfo[20].ModelB = KNUCKLES_OBJECTS[39];
	NPCKnucklesWeldInfo[20].anonymous_5 = 0;
	NPCKnucklesWeldInfo[20].VertexBuffer = 0;
	NPCKnucklesWeldInfo[20].VertexPairCount = (uint8_t)(LengthOfArray(Knuckles_ShoeIndices) / 2);
	NPCKnucklesWeldInfo[20].WeldType = 2;
	NPCKnucklesWeldInfo[20].VertIndexes = Knuckles_ShoeIndices;
	NPCKnucklesWeldInfo[21].BaseModel = KNUCKLES_OBJECTS[1];
	NPCKnucklesWeldInfo[21].ModelA = KNUCKLES_OBJECTS[40];
	v3 = KNUCKLES_OBJECTS[41];
	NPCKnucklesWeldInfo[21].anonymous_5 = 0;
	NPCKnucklesWeldInfo[21].VertexBuffer = 0;
	NPCKnucklesWeldInfo[21].ModelB = v3;
	NPCKnucklesWeldInfo[21].VertIndexes = Knuckles_ShoeIndices;
	NPCKnucklesWeldInfo[21].VertexPairCount = (uint8_t)(LengthOfArray(Knuckles_ShoeIndices) / 2);
	NPCKnucklesWeldInfo[21].WeldType = 2;
	NPCKnucklesWeldInfo[22].BaseModel = KNUCKLES_OBJECTS[1];
	NPCKnucklesWeldInfo[22].ModelA = KNUCKLES_OBJECTS[42];
	v4 = KNUCKLES_OBJECTS[27];
	NPCKnucklesWeldInfo[22].anonymous_5 = 0;
	NPCKnucklesWeldInfo[22].VertexBuffer = 0;
	NPCKnucklesWeldInfo[22].ModelB = v4;
	NPCKnucklesWeldInfo[22].VertIndexes = Knuckles_HandIndices;
	NPCKnucklesWeldInfo[22].VertexPairCount = (uint8_t)(LengthOfArray(Knuckles_HandIndices) / 2);
	NPCKnucklesWeldInfo[22].WeldType = 2;
	NPCKnucklesWeldInfo[23].BaseModel = KNUCKLES_OBJECTS[1];
	NPCKnucklesWeldInfo[23].ModelA = KNUCKLES_OBJECTS[44];
	v5 = KNUCKLES_OBJECTS[31];
	NPCKnucklesWeldInfo[23].anonymous_5 = 0;
	NPCKnucklesWeldInfo[23].VertexBuffer = 0;
	NPCKnucklesWeldInfo[24].BaseModel = 0;
	NPCKnucklesWeldInfo[24].ModelA = 0;
	NPCKnucklesWeldInfo[23].VertIndexes = Knuckles_HandIndices;
	NPCKnucklesWeldInfo[24].ModelB = 0;
	NPCKnucklesWeldInfo[24].VertexPairCount = 0;
	NPCKnucklesWeldInfo[24].VertexBuffer = 0;
	NPCKnucklesWeldInfo[23].ModelB = v5;
	NPCKnucklesWeldInfo[23].VertexPairCount = (uint8_t)(LengthOfArray(Knuckles_HandIndices) / 2);
	NPCKnucklesWeldInfo[23].WeldType = 2;
	NPCKnucklesWeldInfo[24].VertIndexes = 0;
}

void __cdecl Knuckles_Upgrades_c(CharObj2 *a1)
{
	unsigned __int16 *v1; // eax@2

	switch (a1->Upgrades & 0x60)
	{
	case 0:
		KNUCKLES_OBJECTS[58]->model = KNUCKLES_MODELS[7];
		KNUCKLES_OBJECTS[59]->model = KNUCKLES_MODELS[8];
		KNUCKLES_OBJECTS[60]->model = KNUCKLES_MODELS[9];
		KNUCKLES_OBJECTS[61]->model = KNUCKLES_MODELS[10];
		KNUCKLES_OBJECTS[62]->model = KNUCKLES_MODELS[11];
		KNUCKLES_OBJECTS[63]->model = KNUCKLES_MODELS[12];
		KNUCKLES_OBJECTS[64]->model = KNUCKLES_MODELS[13];
		KNUCKLES_OBJECTS[65]->model = KNUCKLES_MODELS[14];
		KNUCKLES_OBJECTS[66]->model = KNUCKLES_MODELS[7];
		KNUCKLES_OBJECTS[67]->model = KNUCKLES_MODELS[8];
		KNUCKLES_OBJECTS[68]->model = KNUCKLES_MODELS[9];
		KNUCKLES_OBJECTS[69]->model = KNUCKLES_MODELS[10];
		KNUCKLES_OBJECTS[70]->model = KNUCKLES_MODELS[11];
		KNUCKLES_OBJECTS[71]->model = KNUCKLES_MODELS[12];
		KNUCKLES_OBJECTS[72]->model = KNUCKLES_MODELS[13];
		KNUCKLES_OBJECTS[73]->model = KNUCKLES_MODELS[14];
		v1 = (unsigned __int16 *)&Knuckles_HandIndices;
		goto LABEL_7;
	case 0x40:
		KNUCKLES_OBJECTS[58]->model = KNUCKLES_MODELS[7];
		KNUCKLES_OBJECTS[59]->model = KNUCKLES_MODELS[8];
		KNUCKLES_OBJECTS[60]->model = *KNUCKLES_MODELS;
		KNUCKLES_OBJECTS[61]->model = KNUCKLES_MODELS[10];
		KNUCKLES_OBJECTS[62]->model = KNUCKLES_MODELS[11];
		KNUCKLES_OBJECTS[63]->model = KNUCKLES_MODELS[12];
		KNUCKLES_OBJECTS[64]->model = KNUCKLES_MODELS[2];
		KNUCKLES_OBJECTS[65]->model = KNUCKLES_MODELS[14];
		KNUCKLES_OBJECTS[66]->model = KNUCKLES_MODELS[7];
		KNUCKLES_OBJECTS[67]->model = KNUCKLES_MODELS[8];
		KNUCKLES_OBJECTS[68]->model = *KNUCKLES_MODELS;
		KNUCKLES_OBJECTS[69]->model = KNUCKLES_MODELS[10];
		KNUCKLES_OBJECTS[70]->model = KNUCKLES_MODELS[11];
		KNUCKLES_OBJECTS[71]->model = KNUCKLES_MODELS[12];
		KNUCKLES_OBJECTS[72]->model = KNUCKLES_MODELS[2];
		KNUCKLES_OBJECTS[73]->model = KNUCKLES_MODELS[14];
		goto LABEL_6;
	case 0x20:
		KNUCKLES_OBJECTS[58]->model = KNUCKLES_MODELS[15];
		KNUCKLES_OBJECTS[59]->model = KNUCKLES_MODELS[16];
		KNUCKLES_OBJECTS[60]->model = KNUCKLES_MODELS[17];
		KNUCKLES_OBJECTS[61]->model = KNUCKLES_MODELS[18];
		KNUCKLES_OBJECTS[62]->model = KNUCKLES_MODELS[19];
		KNUCKLES_OBJECTS[63]->model = KNUCKLES_MODELS[20];
		KNUCKLES_OBJECTS[64]->model = KNUCKLES_MODELS[21];
		KNUCKLES_OBJECTS[65]->model = KNUCKLES_MODELS[22];
		KNUCKLES_OBJECTS[66]->model = KNUCKLES_MODELS[15];
		KNUCKLES_OBJECTS[67]->model = KNUCKLES_MODELS[16];
		KNUCKLES_OBJECTS[68]->model = KNUCKLES_MODELS[17];
		KNUCKLES_OBJECTS[69]->model = KNUCKLES_MODELS[18];
		KNUCKLES_OBJECTS[70]->model = KNUCKLES_MODELS[19];
		KNUCKLES_OBJECTS[71]->model = KNUCKLES_MODELS[20];
		KNUCKLES_OBJECTS[72]->model = KNUCKLES_MODELS[21];
		KNUCKLES_OBJECTS[73]->model = KNUCKLES_MODELS[22];
		v1 = (unsigned __int16 *)&Knuckles_HandIndices;
		goto LABEL_7;
	case 0x60:
		KNUCKLES_OBJECTS[58]->model = KNUCKLES_MODELS[15];
		KNUCKLES_OBJECTS[59]->model = KNUCKLES_MODELS[16];
		KNUCKLES_OBJECTS[60]->model = KNUCKLES_MODELS[1];
		KNUCKLES_OBJECTS[61]->model = KNUCKLES_MODELS[18];
		KNUCKLES_OBJECTS[62]->model = KNUCKLES_MODELS[19];
		KNUCKLES_OBJECTS[63]->model = KNUCKLES_MODELS[20];
		KNUCKLES_OBJECTS[64]->model = KNUCKLES_MODELS[3];
		KNUCKLES_OBJECTS[65]->model = KNUCKLES_MODELS[22];
		KNUCKLES_OBJECTS[66]->model = KNUCKLES_MODELS[15];
		KNUCKLES_OBJECTS[67]->model = KNUCKLES_MODELS[16];
		KNUCKLES_OBJECTS[68]->model = KNUCKLES_MODELS[1];
		KNUCKLES_OBJECTS[69]->model = KNUCKLES_MODELS[18];
		KNUCKLES_OBJECTS[70]->model = KNUCKLES_MODELS[19];
		KNUCKLES_OBJECTS[71]->model = KNUCKLES_MODELS[20];
		KNUCKLES_OBJECTS[72]->model = KNUCKLES_MODELS[3];
		KNUCKLES_OBJECTS[73]->model = KNUCKLES_MODELS[22];
	LABEL_6:
		v1 = (unsigned __int16 *)&Knuckles_ShovelClawIndices;
	LABEL_7:
		KnucklesWeldInfo[23].VertIndexes = v1;
		KnucklesWeldInfo[22].VertIndexes = v1;
		KnucklesWeldInfo[11].VertIndexes = v1;
		KnucklesWeldInfo[10].VertIndexes = v1;
		NPCKnucklesWeldInfo[23].VertIndexes = v1;
		NPCKnucklesWeldInfo[22].VertIndexes = v1;
		NPCKnucklesWeldInfo[11].VertIndexes = v1;
		NPCKnucklesWeldInfo[10].VertIndexes = v1;
		break;
	default:
		return;
	}
}

static void __declspec(naked) Knuckles_Upgrades_mod()
{
	__asm
	{
		push eax // a1

				 // Call your __cdecl function here:
				 call Knuckles_Upgrades_c

				 pop eax // a1
				 retn
	}
}

void __cdecl InitAmyWeldInfo_mod()
{
	NJS_OBJECT *v0; // edi@1
	NJS_OBJECT *v1; // edi@1
	NJS_OBJECT *v2; // edi@1
	NJS_OBJECT *v3; // edi@1
	NJS_OBJECT *v4; // esi@1
	NJS_OBJECT *v5; // edx@1
	NJS_OBJECT *v6; // edx@1
	NJS_OBJECT *v7; // eax@1

	AmyWeldInfo[0].BaseModel = *AMY_OBJECTS;
	AmyWeldInfo[0].ModelA = AMY_OBJECTS[6];
	AmyWeldInfo[0].ModelB = AMY_OBJECTS[7];
	AmyWeldInfo[0].anonymous_5 = 0;
	AmyWeldInfo[0].VertexBuffer = 0;
	AmyWeldInfo[0].VertexPairCount = (uint8_t)(LengthOfArray(Amy_UpperArmIndices) / 2);
	AmyWeldInfo[0].WeldType = 2;
	AmyWeldInfo[0].VertIndexes = Amy_UpperArmIndices;
	AmyWeldInfo[1].BaseModel = *AMY_OBJECTS;
	AmyWeldInfo[1].ModelA = AMY_OBJECTS[7];
	AmyWeldInfo[1].ModelB = AMY_OBJECTS[8];
	AmyWeldInfo[1].VertexPairCount = (uint8_t)(LengthOfArray(Amy_LowerArmIndices) / 2);
	AmyWeldInfo[1].WeldType = 2;
	AmyWeldInfo[1].anonymous_5 = 0;
	AmyWeldInfo[1].VertexBuffer = 0;
	AmyWeldInfo[1].VertIndexes = Amy_LowerArmIndices;
	AmyWeldInfo[2].BaseModel = *AMY_OBJECTS;
	AmyWeldInfo[2].ModelA = AMY_OBJECTS[9];
	AmyWeldInfo[2].ModelB = AMY_OBJECTS[10];
	AmyWeldInfo[2].VertexPairCount = (uint8_t)(LengthOfArray(Amy_UpperArmIndices) / 2);
	AmyWeldInfo[2].WeldType = 2;
	AmyWeldInfo[2].anonymous_5 = 0;
	AmyWeldInfo[2].VertexBuffer = 0;
	AmyWeldInfo[2].VertIndexes = Amy_UpperArmIndices;
	AmyWeldInfo[3].BaseModel = *AMY_OBJECTS;
	AmyWeldInfo[3].ModelA = AMY_OBJECTS[10];
	v0 = AMY_OBJECTS[11];
	AmyWeldInfo[3].VertIndexes = Amy_LowerArmIndices;
	AmyWeldInfo[3].ModelB = v0;
	AmyWeldInfo[3].VertexPairCount = (uint8_t)(LengthOfArray(Amy_LowerArmIndices) / 2);
	AmyWeldInfo[3].WeldType = 2;
	AmyWeldInfo[3].anonymous_5 = 0;
	AmyWeldInfo[3].VertexBuffer = 0;
	AmyWeldInfo[4].BaseModel = *AMY_OBJECTS;
	AmyWeldInfo[4].ModelA = AMY_OBJECTS[12];
	AmyWeldInfo[4].ModelB = AMY_OBJECTS[13];
	AmyWeldInfo[4].VertexPairCount = (uint8_t)(LengthOfArray(Amy_LegIndices) / 2);
	AmyWeldInfo[4].WeldType = 2;
	AmyWeldInfo[4].anonymous_5 = 0;
	AmyWeldInfo[4].VertexBuffer = 0;
	AmyWeldInfo[4].VertIndexes = Amy_LegIndices;
	AmyWeldInfo[5].BaseModel = *AMY_OBJECTS;
	AmyWeldInfo[5].ModelA = AMY_OBJECTS[13];
	AmyWeldInfo[5].ModelB = AMY_OBJECTS[14];
	AmyWeldInfo[5].VertexPairCount = (uint8_t)(LengthOfArray(Amy_LegIndices) / 2);
	AmyWeldInfo[5].WeldType = 2;
	AmyWeldInfo[5].anonymous_5 = 0;
	AmyWeldInfo[5].VertIndexes = Amy_LegIndices;
	AmyWeldInfo[5].VertexBuffer = 0;
	AmyWeldInfo[6].BaseModel = *AMY_OBJECTS;
	AmyWeldInfo[6].ModelA = AMY_OBJECTS[15];
	v1 = AMY_OBJECTS[16];
	AmyWeldInfo[6].VertIndexes = Amy_LegIndices;
	AmyWeldInfo[6].ModelB = v1;
	AmyWeldInfo[6].VertexPairCount = (uint8_t)(LengthOfArray(Amy_LegIndices) / 2);
	AmyWeldInfo[6].WeldType = 2;
	AmyWeldInfo[6].anonymous_5 = 0;
	AmyWeldInfo[6].VertexBuffer = 0;
	AmyWeldInfo[7].BaseModel = *AMY_OBJECTS;
	AmyWeldInfo[7].ModelA = AMY_OBJECTS[16];
	v2 = AMY_OBJECTS[17];
	AmyWeldInfo[7].VertIndexes = Amy_LegIndices;
	AmyWeldInfo[7].ModelB = v2;
	AmyWeldInfo[7].VertexPairCount = (uint8_t)(LengthOfArray(Amy_LegIndices) / 2);
	AmyWeldInfo[7].WeldType = 2;
	AmyWeldInfo[7].anonymous_5 = 0;
	AmyWeldInfo[7].VertexBuffer = 0;
	AmyWeldInfo[8].BaseModel = *AMY_OBJECTS;
	AmyWeldInfo[8].ModelA = AMY_OBJECTS[18];
	AmyWeldInfo[8].ModelB = AMY_OBJECTS[19];
	AmyWeldInfo[8].VertexPairCount = (uint8_t)(LengthOfArray(Amy_ShoeIndices) / 2);
	AmyWeldInfo[8].WeldType = 2;
	AmyWeldInfo[8].anonymous_5 = 0;
	AmyWeldInfo[8].VertexBuffer = 0;
	AmyWeldInfo[8].VertIndexes = Amy_ShoeIndices;
	AmyWeldInfo[9].BaseModel = *AMY_OBJECTS;
	AmyWeldInfo[9].ModelA = AMY_OBJECTS[20];
	v3 = AMY_OBJECTS[21];
	AmyWeldInfo[9].VertIndexes = Amy_ShoeIndices;
	AmyWeldInfo[9].ModelB = v3;
	AmyWeldInfo[9].VertexPairCount = (uint8_t)(LengthOfArray(Amy_ShoeIndices) / 2);
	AmyWeldInfo[9].WeldType = 2;
	AmyWeldInfo[9].anonymous_5 = 0;
	AmyWeldInfo[9].VertexBuffer = 0;
	AmyWeldInfo[10].BaseModel = *AMY_OBJECTS;
	AmyWeldInfo[10].ModelA = AMY_OBJECTS[22];
	AmyWeldInfo[10].ModelB = AMY_OBJECTS[23];
	AmyWeldInfo[10].VertexPairCount = (uint8_t)(LengthOfArray(Amy_HandIndices) / 2);
	AmyWeldInfo[10].WeldType = 2;
	AmyWeldInfo[10].anonymous_5 = 0;
	AmyWeldInfo[10].VertexBuffer = 0;
	AmyWeldInfo[10].VertIndexes = Amy_HandIndices;
	AmyWeldInfo[11].BaseModel = *AMY_OBJECTS;
	AmyWeldInfo[11].ModelA = AMY_OBJECTS[24];
	AmyWeldInfo[11].ModelB = AMY_OBJECTS[25];
	AmyWeldInfo[11].VertexPairCount = (uint8_t)(LengthOfArray(Amy_HandIndices) / 2);
	AmyWeldInfo[11].WeldType = 2;
	AmyWeldInfo[11].anonymous_5 = 0;
	AmyWeldInfo[11].VertexBuffer = 0;
	AmyWeldInfo[11].VertIndexes = Amy_HandIndices;
	AmyWeldInfo[12].BaseModel = *AMY_OBJECTS;
	AmyWeldInfo[12].ModelA = AMY_OBJECTS[23];
	AmyWeldInfo[12].ModelB = 0;
	AmyWeldInfo[12].anonymous_5 = 0;
	AmyWeldInfo[12].VertexBuffer = 0;
	AmyWeldInfo[12].VertIndexes = 0;
	AmyWeldInfo[12].WeldType = 4;
	AmyWeldInfo[12].VertexPairCount = 2;
	AmyWeldInfo[13].BaseModel = *AMY_OBJECTS;
	v4 = AMY_OBJECTS[25];
	AmyWeldInfo[13].ModelB = 0;
	AmyWeldInfo[13].anonymous_5 = 0;
	AmyWeldInfo[13].VertexBuffer = 0;
	AmyWeldInfo[13].VertIndexes = 0;
	AmyWeldInfo[13].ModelA = v4;
	AmyWeldInfo[13].VertexPairCount = 2;
	AmyWeldInfo[13].WeldType = 5;
	AmyWeldInfo[14].BaseModel = *AMY_OBJECTS;
	v5 = AMY_OBJECTS[19];
	AmyWeldInfo[14].ModelB = 0;
	AmyWeldInfo[14].VertexPairCount = 0;
	AmyWeldInfo[14].anonymous_5 = 0;
	AmyWeldInfo[14].VertexBuffer = 0;
	AmyWeldInfo[14].VertIndexes = 0;
	AmyWeldInfo[14].ModelA = v5;
	AmyWeldInfo[14].WeldType = 6;
	AmyWeldInfo[15].BaseModel = *AMY_OBJECTS;
	v6 = AMY_OBJECTS[21];
	AmyWeldInfo[15].ModelB = 0;
	AmyWeldInfo[15].VertexPairCount = 0;
	AmyWeldInfo[15].anonymous_5 = 0;
	AmyWeldInfo[15].VertexBuffer = 0;
	AmyWeldInfo[15].VertIndexes = 0;
	AmyWeldInfo[15].ModelA = v6;
	AmyWeldInfo[15].WeldType = 7;
	AmyWeldInfo[16].BaseModel = *AMY_OBJECTS;
	v7 = AMY_OBJECTS[30];
	AmyWeldInfo[16].ModelB = 0;
	AmyWeldInfo[16].VertexPairCount = 0;
	AmyWeldInfo[16].anonymous_5 = 0;
	AmyWeldInfo[16].VertexBuffer = 0;
	AmyWeldInfo[16].VertIndexes = 0;
	AmyWeldInfo[17].BaseModel = 0;
	AmyWeldInfo[17].ModelA = 0;
	AmyWeldInfo[17].ModelB = 0;
	AmyWeldInfo[17].VertexPairCount = 0;
	AmyWeldInfo[17].VertexBuffer = 0;
	AmyWeldInfo[16].ModelA = v7;
	AmyWeldInfo[16].WeldType = 8;
	AmyWeldInfo[17].VertIndexes = 0;
}

void __cdecl InitNPCAmyWeldInfo_mod()
{
	NJS_OBJECT *v0; // edi@1
	NJS_OBJECT *v1; // edi@1
	NJS_OBJECT *v2; // edi@1
	NJS_OBJECT *v3; // edi@1
	NJS_OBJECT *v4; // eax@1

	NPCAmyWeldInfo[0].BaseModel = *AMY_OBJECTS;
	NPCAmyWeldInfo[0].ModelA = AMY_OBJECTS[6];
	NPCAmyWeldInfo[0].ModelB = AMY_OBJECTS[7];
	NPCAmyWeldInfo[0].anonymous_5 = 0;
	NPCAmyWeldInfo[0].VertexBuffer = 0;
	NPCAmyWeldInfo[0].VertexPairCount = (uint8_t)(LengthOfArray(Amy_UpperArmIndices) / 2);
	NPCAmyWeldInfo[0].WeldType = 2;
	NPCAmyWeldInfo[0].VertIndexes = Amy_UpperArmIndices;
	NPCAmyWeldInfo[1].BaseModel = *AMY_OBJECTS;
	NPCAmyWeldInfo[1].ModelA = AMY_OBJECTS[7];
	NPCAmyWeldInfo[1].ModelB = AMY_OBJECTS[8];
	NPCAmyWeldInfo[1].VertexPairCount = (uint8_t)(LengthOfArray(Amy_LowerArmIndices) / 2);
	NPCAmyWeldInfo[1].WeldType = 2;
	NPCAmyWeldInfo[1].anonymous_5 = 0;
	NPCAmyWeldInfo[1].VertexBuffer = 0;
	NPCAmyWeldInfo[1].VertIndexes = Amy_LowerArmIndices;
	NPCAmyWeldInfo[2].BaseModel = *AMY_OBJECTS;
	NPCAmyWeldInfo[2].ModelA = AMY_OBJECTS[9];
	NPCAmyWeldInfo[2].ModelB = AMY_OBJECTS[10];
	NPCAmyWeldInfo[2].VertexPairCount = (uint8_t)(LengthOfArray(Amy_UpperArmIndices) / 2);
	NPCAmyWeldInfo[2].WeldType = 2;
	NPCAmyWeldInfo[2].anonymous_5 = 0;
	NPCAmyWeldInfo[2].VertexBuffer = 0;
	NPCAmyWeldInfo[2].VertIndexes = Amy_UpperArmIndices;
	NPCAmyWeldInfo[3].BaseModel = *AMY_OBJECTS;
	NPCAmyWeldInfo[3].ModelA = AMY_OBJECTS[10];
	v0 = AMY_OBJECTS[11];
	NPCAmyWeldInfo[3].VertIndexes = Amy_LowerArmIndices;
	NPCAmyWeldInfo[3].ModelB = v0;
	NPCAmyWeldInfo[3].VertexPairCount = (uint8_t)(LengthOfArray(Amy_LowerArmIndices) / 2);
	NPCAmyWeldInfo[3].WeldType = 2;
	NPCAmyWeldInfo[3].anonymous_5 = 0;
	NPCAmyWeldInfo[3].VertexBuffer = 0;
	NPCAmyWeldInfo[4].BaseModel = *AMY_OBJECTS;
	NPCAmyWeldInfo[4].ModelA = AMY_OBJECTS[12];
	NPCAmyWeldInfo[4].ModelB = AMY_OBJECTS[13];
	NPCAmyWeldInfo[4].VertexPairCount = (uint8_t)(LengthOfArray(Amy_LegIndices) / 2);
	NPCAmyWeldInfo[4].WeldType = 2;
	NPCAmyWeldInfo[4].anonymous_5 = 0;
	NPCAmyWeldInfo[4].VertexBuffer = 0;
	NPCAmyWeldInfo[4].VertIndexes = Amy_LegIndices;
	NPCAmyWeldInfo[5].BaseModel = *AMY_OBJECTS;
	NPCAmyWeldInfo[5].ModelA = AMY_OBJECTS[13];
	NPCAmyWeldInfo[5].ModelB = AMY_OBJECTS[14];
	NPCAmyWeldInfo[5].VertexPairCount = (uint8_t)(LengthOfArray(Amy_LegIndices) / 2);
	NPCAmyWeldInfo[5].WeldType = 2;
	NPCAmyWeldInfo[5].anonymous_5 = 0;
	NPCAmyWeldInfo[5].VertexBuffer = 0;
	NPCAmyWeldInfo[5].VertIndexes = Amy_LegIndices;
	NPCAmyWeldInfo[6].BaseModel = *AMY_OBJECTS;
	NPCAmyWeldInfo[6].ModelA = AMY_OBJECTS[15];
	v1 = AMY_OBJECTS[16];
	NPCAmyWeldInfo[6].VertexPairCount = (uint8_t)(LengthOfArray(Amy_LegIndices) / 2);
	NPCAmyWeldInfo[6].anonymous_5 = 0;
	NPCAmyWeldInfo[6].VertexBuffer = 0;
	NPCAmyWeldInfo[6].VertIndexes = Amy_LegIndices;
	NPCAmyWeldInfo[6].ModelB = v1;
	NPCAmyWeldInfo[6].WeldType = 2;
	NPCAmyWeldInfo[7].BaseModel = *AMY_OBJECTS;
	NPCAmyWeldInfo[7].ModelA = AMY_OBJECTS[16];
	v2 = AMY_OBJECTS[17];
	NPCAmyWeldInfo[7].VertexPairCount = (uint8_t)(LengthOfArray(Amy_LegIndices) / 2);
	NPCAmyWeldInfo[7].anonymous_5 = 0;
	NPCAmyWeldInfo[7].VertexBuffer = 0;
	NPCAmyWeldInfo[7].VertIndexes = Amy_LegIndices;
	NPCAmyWeldInfo[7].ModelB = v2;
	NPCAmyWeldInfo[7].WeldType = 2;
	NPCAmyWeldInfo[8].BaseModel = *AMY_OBJECTS;
	NPCAmyWeldInfo[8].ModelA = AMY_OBJECTS[18];
	NPCAmyWeldInfo[8].ModelB = AMY_OBJECTS[19];
	NPCAmyWeldInfo[8].anonymous_5 = 0;
	NPCAmyWeldInfo[8].VertexBuffer = 0;
	NPCAmyWeldInfo[8].WeldType = 2;
	NPCAmyWeldInfo[8].VertexPairCount = (uint8_t)(LengthOfArray(Amy_ShoeIndices) / 2);
	NPCAmyWeldInfo[8].VertIndexes = Amy_ShoeIndices;
	NPCAmyWeldInfo[9].BaseModel = *AMY_OBJECTS;
	NPCAmyWeldInfo[9].ModelA = AMY_OBJECTS[20];
	v3 = AMY_OBJECTS[21];
	NPCAmyWeldInfo[9].anonymous_5 = 0;
	NPCAmyWeldInfo[9].VertexBuffer = 0;
	NPCAmyWeldInfo[9].VertexPairCount = (uint8_t)(LengthOfArray(Amy_ShoeIndices) / 2);
	NPCAmyWeldInfo[9].VertIndexes = Amy_ShoeIndices;
	NPCAmyWeldInfo[9].ModelB = v3;
	NPCAmyWeldInfo[9].WeldType = 2;
	NPCAmyWeldInfo[10].BaseModel = *AMY_OBJECTS;
	NPCAmyWeldInfo[10].ModelA = AMY_OBJECTS[22];
	NPCAmyWeldInfo[10].ModelB = AMY_OBJECTS[23];
	NPCAmyWeldInfo[10].anonymous_5 = 0;
	NPCAmyWeldInfo[10].VertexBuffer = 0;
	NPCAmyWeldInfo[10].VertexPairCount = (uint8_t)(LengthOfArray(Amy_HandIndices) / 2);
	NPCAmyWeldInfo[10].WeldType = 2;
	NPCAmyWeldInfo[10].VertIndexes = Amy_HandIndices;
	NPCAmyWeldInfo[11].BaseModel = *AMY_OBJECTS;
	NPCAmyWeldInfo[11].ModelA = AMY_OBJECTS[24];
	v4 = AMY_OBJECTS[25];
	NPCAmyWeldInfo[11].anonymous_5 = 0;
	NPCAmyWeldInfo[11].VertexBuffer = 0;
	NPCAmyWeldInfo[12].BaseModel = 0;
	NPCAmyWeldInfo[12].ModelA = 0;
	NPCAmyWeldInfo[11].ModelB = v4;
	NPCAmyWeldInfo[11].VertexPairCount = (uint8_t)(LengthOfArray(Amy_HandIndices) / 2);
	NPCAmyWeldInfo[11].WeldType = 2;
	NPCAmyWeldInfo[11].VertIndexes = Amy_HandIndices;
	NPCAmyWeldInfo[12].ModelB = 0;
	NPCAmyWeldInfo[12].VertexPairCount = 0;
	NPCAmyWeldInfo[12].VertexBuffer = 0;
	NPCAmyWeldInfo[12].VertIndexes = 0;
}

void __cdecl InitBigWeldInfo_mod()
{
	NJS_OBJECT *v0; // ebp@1
	NJS_OBJECT *v1; // edi@1
	NJS_OBJECT *v2; // edi@1
	NJS_OBJECT *v3; // edx@1
	NJS_OBJECT *v4; // edx@1
	NJS_OBJECT *v5; // eax@1

	BigWeldInfo[0].BaseModel = *BIG_OBJECTS;
	BigWeldInfo[0].ModelA = BIG_OBJECTS[2];
	BigWeldInfo[0].ModelB = BIG_OBJECTS[3];
	BigWeldInfo[0].anonymous_5 = 0;
	BigWeldInfo[0].VertexBuffer = 0;
	BigWeldInfo[0].VertexPairCount = (uint8_t)(LengthOfArray(vi_00519968) / 2);
	BigWeldInfo[0].WeldType = 1;
	BigWeldInfo[0].VertIndexes = vi_00519968;
	BigWeldInfo[1].BaseModel = *BIG_OBJECTS;
	BigWeldInfo[1].ModelA = BIG_OBJECTS[3];
	BigWeldInfo[1].ModelB = BIG_OBJECTS[4];
	BigWeldInfo[1].WeldType = 1;
	BigWeldInfo[1].VertexPairCount = (uint8_t)(LengthOfArray(vi_00519980) / 2);
	BigWeldInfo[1].anonymous_5 = 0;
	BigWeldInfo[1].VertexBuffer = 0;
	BigWeldInfo[1].VertIndexes = vi_00519980;
	BigWeldInfo[2].BaseModel = *BIG_OBJECTS;
	BigWeldInfo[2].ModelA = BIG_OBJECTS[6];
	v0 = BIG_OBJECTS[7];
	BigWeldInfo[2].WeldType = 1;
	BigWeldInfo[2].ModelB = v0;
	BigWeldInfo[2].VertexPairCount = (uint8_t)(LengthOfArray(vi_00519968) / 2);
	BigWeldInfo[2].anonymous_5 = 0;
	BigWeldInfo[2].VertexBuffer = 0;
	BigWeldInfo[2].VertIndexes = vi_00519968;
	BigWeldInfo[3].BaseModel = *BIG_OBJECTS;
	BigWeldInfo[3].ModelA = BIG_OBJECTS[7];
	v1 = BIG_OBJECTS[8];
	BigWeldInfo[3].WeldType = 1;
	BigWeldInfo[3].VertIndexes = vi_00519980;
	BigWeldInfo[3].ModelB = v1;
	BigWeldInfo[3].VertexPairCount = (uint8_t)(LengthOfArray(vi_00519980) / 2);
	BigWeldInfo[3].anonymous_5 = 0;
	BigWeldInfo[3].VertexBuffer = 0;
	BigWeldInfo[4].BaseModel = *BIG_OBJECTS;
	BigWeldInfo[4].ModelA = BIG_OBJECTS[14];
	BigWeldInfo[4].ModelB = BIG_OBJECTS[15];
	BigWeldInfo[4].VertexPairCount = (uint8_t)(LengthOfArray(vi_00519998) / 2);
	BigWeldInfo[4].WeldType = 2;
	BigWeldInfo[4].anonymous_5 = 0;
	BigWeldInfo[4].VertexBuffer = 0;
	BigWeldInfo[4].VertIndexes = vi_00519998;
	BigWeldInfo[5].BaseModel = *BIG_OBJECTS;
	BigWeldInfo[5].ModelA = BIG_OBJECTS[10];
	BigWeldInfo[5].ModelB = BIG_OBJECTS[11];
	BigWeldInfo[5].VertexPairCount = (uint8_t)(LengthOfArray(vi_00519998) / 2);
	BigWeldInfo[5].WeldType = 2;
	BigWeldInfo[5].anonymous_5 = 0;
	BigWeldInfo[5].VertIndexes = vi_00519998;
	BigWeldInfo[5].VertexBuffer = 0;
	BigWeldInfo[6].BaseModel = *BIG_OBJECTS;
	BigWeldInfo[6].ModelA = BIG_OBJECTS[16];
	BigWeldInfo[6].ModelB = BIG_OBJECTS[17];
	BigWeldInfo[6].VertexPairCount = (uint8_t)(LengthOfArray(vi_005199B0) / 2);
	BigWeldInfo[6].WeldType = 2;
	BigWeldInfo[6].anonymous_5 = 0;
	BigWeldInfo[6].VertexBuffer = 0;
	BigWeldInfo[6].VertIndexes = vi_005199B0;
	BigWeldInfo[7].BaseModel = *BIG_OBJECTS;
	BigWeldInfo[7].ModelA = BIG_OBJECTS[12];
	v2 = BIG_OBJECTS[13];
	BigWeldInfo[7].VertIndexes = vi_005199B0;
	BigWeldInfo[7].ModelB = v2;
	BigWeldInfo[7].VertexPairCount = (uint8_t)(LengthOfArray(vi_005199B0) / 2);
	BigWeldInfo[7].WeldType = 2;
	BigWeldInfo[7].anonymous_5 = 0;
	BigWeldInfo[7].VertexBuffer = 0;
	BigWeldInfo[8].BaseModel = *BIG_OBJECTS;
	BigWeldInfo[8].ModelA = BIG_OBJECTS[18];
	BigWeldInfo[8].ModelB = BIG_OBJECTS[5];
	BigWeldInfo[8].VertexPairCount = (uint8_t)(LengthOfArray(B_Hand) / 2);
	BigWeldInfo[8].WeldType = 2;
	BigWeldInfo[8].anonymous_5 = 0;
	BigWeldInfo[8].VertexBuffer = 0;
	BigWeldInfo[8].VertIndexes = B_Hand;
	BigWeldInfo[9].BaseModel = *BIG_OBJECTS;
	BigWeldInfo[9].ModelA = BIG_OBJECTS[20];
	BigWeldInfo[9].ModelB = BIG_OBJECTS[9];
	BigWeldInfo[9].VertexPairCount = (uint8_t)(LengthOfArray(B_Hand) / 2);
	BigWeldInfo[9].WeldType = 2;
	BigWeldInfo[9].anonymous_5 = 0;
	BigWeldInfo[9].VertexBuffer = 0;
	BigWeldInfo[9].VertIndexes = B_Hand;
	BigWeldInfo[10].BaseModel = *BIG_OBJECTS;
	BigWeldInfo[10].ModelA = BIG_OBJECTS[5];
	BigWeldInfo[10].ModelB = 0;
	BigWeldInfo[10].VertexPairCount = 2;
	BigWeldInfo[10].WeldType = 4;
	BigWeldInfo[10].anonymous_5 = 0;
	BigWeldInfo[10].VertexBuffer = 0;
	BigWeldInfo[10].VertIndexes = 0;
	BigWeldInfo[11].BaseModel = *BIG_OBJECTS;
	BigWeldInfo[11].ModelA = BIG_OBJECTS[9];
	BigWeldInfo[11].ModelB = 0;
	BigWeldInfo[11].VertexPairCount = 2;
	BigWeldInfo[11].WeldType = 5;
	BigWeldInfo[11].anonymous_5 = 0;
	BigWeldInfo[11].VertexBuffer = 0;
	BigWeldInfo[11].VertIndexes = 0;
	BigWeldInfo[12].BaseModel = *BIG_OBJECTS;
	BigWeldInfo[12].ModelA = BIG_OBJECTS[17];
	BigWeldInfo[12].ModelB = 0;
	BigWeldInfo[12].VertexPairCount = 0;
	BigWeldInfo[12].anonymous_5 = 0;
	BigWeldInfo[12].VertexBuffer = 0;
	BigWeldInfo[12].VertIndexes = 0;
	BigWeldInfo[12].WeldType = 6;
	BigWeldInfo[13].BaseModel = *BIG_OBJECTS;
	v3 = BIG_OBJECTS[13];
	BigWeldInfo[13].ModelB = 0;
	BigWeldInfo[13].VertexPairCount = 0;
	BigWeldInfo[13].anonymous_5 = 0;
	BigWeldInfo[13].VertexBuffer = 0;
	BigWeldInfo[13].VertIndexes = 0;
	BigWeldInfo[13].ModelA = v3;
	BigWeldInfo[13].WeldType = 7;
	BigWeldInfo[14].BaseModel = *BIG_OBJECTS;
	v4 = BIG_OBJECTS[25];
	BigWeldInfo[14].ModelB = 0;
	BigWeldInfo[14].VertexPairCount = 0;
	BigWeldInfo[14].anonymous_5 = 0;
	BigWeldInfo[14].VertexBuffer = 0;
	BigWeldInfo[14].VertIndexes = 0;
	BigWeldInfo[14].ModelA = v4;
	BigWeldInfo[14].WeldType = 8;
	BigWeldInfo[15].BaseModel = *BIG_OBJECTS;
	v5 = BIG_OBJECTS[26];
	BigWeldInfo[15].ModelB = 0;
	BigWeldInfo[15].VertexPairCount = 0;
	BigWeldInfo[15].anonymous_5 = 0;
	BigWeldInfo[15].VertexBuffer = 0;
	BigWeldInfo[15].VertIndexes = 0;
	BigWeldInfo[16].BaseModel = 0;
	BigWeldInfo[16].ModelA = 0;
	BigWeldInfo[16].ModelB = 0;
	BigWeldInfo[16].VertexPairCount = 0;
	BigWeldInfo[16].VertexBuffer = 0;
	BigWeldInfo[15].ModelA = v5;
	BigWeldInfo[15].WeldType = 9;
	BigWeldInfo[16].VertIndexes = 0;
}

extern "C" __declspec(dllexport) void __cdecl Init(const char *path, const HelperFunctions &helperFunctions)
{
	HMODULE handle = GetModuleHandle(L"CHRMODELS_orig");

	//Sonic Data for DLL Export
	ResizeTextureList((NJS_TEXLIST *)0x91CB58, 28);
	NJS_OBJECT **___SONIC_OBJECTS = (NJS_OBJECT **)GetProcAddress(handle, "___SONIC_OBJECTS");
	SONIC_OBJECTS = ___SONIC_OBJECTS;
	NJS_ACTION **___SONIC_ACTIONS = (NJS_ACTION **)GetProcAddress(handle, "___SONIC_ACTIONS");
	SONIC_ACTIONS = ___SONIC_ACTIONS;
	NJS_MODEL_SADX **___SONIC_MODELS = (NJS_MODEL_SADX **)GetProcAddress(handle, "___SONIC_MODELS");
	SONIC_MODELS = ___SONIC_MODELS;
	NJS_MOTION **___SONIC_MOTIONS = (NJS_MOTION **)GetProcAddress(handle, "___SONIC_MOTIONS");
	SONIC_MOTIONS = ___SONIC_MOTIONS;
	___SONIC_OBJECTS[0] = &object_0056AF50;
	___SONIC_OBJECTS[1] = &object_00563B7C;
	___SONIC_OBJECTS[2] = &object_00563D0C;
	___SONIC_OBJECTS[3] = &object_005654EC;
	___SONIC_OBJECTS[4] = &object_00564CD0;
	___SONIC_OBJECTS[5] = &object_005647B8;
	___SONIC_OBJECTS[6] = &object_00564A78;
	___SONIC_OBJECTS[7] = &object_00561F14;
	___SONIC_OBJECTS[8] = &object_005620A4;
	___SONIC_OBJECTS[9] = &object_005638CC;
	___SONIC_OBJECTS[10] = &object_005630B0;
	___SONIC_OBJECTS[11] = &object_00562B80;
	___SONIC_OBJECTS[12] = &object_0056044C;
	___SONIC_OBJECTS[13] = &object_005605DC;
	___SONIC_OBJECTS[14] = &object_00561C68;
	___SONIC_OBJECTS[15] = &object_005613F8;
	___SONIC_OBJECTS[16] = &object_00560DD0;
	___SONIC_OBJECTS[17] = &object_0055E99C;
	___SONIC_OBJECTS[18] = &object_0055EB2C;
	___SONIC_OBJECTS[19] = &object_005601B8;
	___SONIC_OBJECTS[20] = &object_0055F948;
	___SONIC_OBJECTS[21] = &object_0055F330;
	___SONIC_OBJECTS[22] = &object_0062DE88;
	___SONIC_OBJECTS[23] = &object_00626AB4;
	___SONIC_OBJECTS[24] = &object_00626C44;
	___SONIC_OBJECTS[25] = &object_0062840C;
	___SONIC_OBJECTS[26] = &object_00627BF0;
	___SONIC_OBJECTS[27] = &object_006276D8;
	___SONIC_OBJECTS[28] = &object_00624E3C;
	___SONIC_OBJECTS[29] = &object_00624FCC;
	___SONIC_OBJECTS[30] = &object_006267F4;
	___SONIC_OBJECTS[31] = &object_00625FD8;
	___SONIC_OBJECTS[32] = &object_00625AA8;
	___SONIC_OBJECTS[33] = &object_00623474;
	___SONIC_OBJECTS[34] = &object_00623604;
	___SONIC_OBJECTS[35] = &object_00624B78;
	___SONIC_OBJECTS[36] = &object_00624308;
	___SONIC_OBJECTS[37] = &object_00623C14;
	___SONIC_OBJECTS[38] = &object_00621AC4;
	___SONIC_OBJECTS[39] = &object_00621C54;
	___SONIC_OBJECTS[40] = &object_006231E0;
	___SONIC_OBJECTS[41] = &object_00622970;
	___SONIC_OBJECTS[42] = &object_00622254;
	___SONIC_OBJECTS[44] = &object_0057BC44;
	___SONIC_OBJECTS[45] = &object_0056998C;
	___SONIC_OBJECTS[46] = &object_00569594;
	___SONIC_OBJECTS[47] = &object_005812AC;
	___SONIC_OBJECTS[48] = &object_00569DEC;
	___SONIC_OBJECTS[49] = &object_00569594;
	___SONIC_OBJECTS[50] = &object_00569E20;
	___SONIC_OBJECTS[51] = &object_00569CE8;
	___SONIC_OBJECTS[52] = &object_005698F0;
	___SONIC_OBJECTS[54] = &object_006837E8;
	___SONIC_OBJECTS[55] = &object_00682EF4;
	___SONIC_OBJECTS[58] = &object_00581FB8;
	___SONIC_OBJECTS[59] = &object_005818AC;
	___SONIC_OBJECTS[60] = &object_00582CC0;
	___SONIC_OBJECTS[61] = &object_005825A4;
	___SONIC_OBJECTS[62] = &object_00565520;
	___SONIC_OBJECTS[63] = &object_00583284;
	___SONIC_OBJECTS[64] = &object_00583904;
	___SONIC_OBJECTS[65] = &object_00585EB4;
	___SONIC_OBJECTS[66] = &object_005729CC;
	___SONIC_OBJECTS[67] = &object_0057BC44;
	___SONIC_ACTIONS[0]->object = &object_0056AF50;
	___SONIC_ACTIONS[1]->object = &object_0056AF50;
	___SONIC_ACTIONS[2]->object = &object_0056AF50;
	___SONIC_ACTIONS[3]->object = &object_0056AF50;
	___SONIC_ACTIONS[4]->object = &object_0056AF50;
	___SONIC_ACTIONS[5]->object = &object_0056AF50;
	___SONIC_ACTIONS[6]->object = &object_0056AF50;
	___SONIC_ACTIONS[7]->object = &object_0056AF50;
	___SONIC_ACTIONS[8]->object = &object_0056AF50;
	___SONIC_ACTIONS[9]->object = &object_0056AF50;
	___SONIC_ACTIONS[10]->object = &object_0056AF50;
	___SONIC_ACTIONS[11]->object = &object_0056AF50;
	___SONIC_ACTIONS[12]->object = &object_0056AF50;
	___SONIC_ACTIONS[13]->object = &object_0056AF50;
	___SONIC_ACTIONS[14]->object = &object_005729CC;
	___SONIC_ACTIONS[15]->object = &object_0056AF50;
	___SONIC_ACTIONS[16]->object = &object_0056AF50;
	___SONIC_ACTIONS[17]->object = &object_0056AF50;
	___SONIC_ACTIONS[18]->object = &object_0056AF50;
	___SONIC_ACTIONS[19]->object = &object_0056AF50;
	___SONIC_ACTIONS[20]->object = &object_0056AF50;
	___SONIC_ACTIONS[21]->object = &object_0057BC44;
	___SONIC_ACTIONS[22]->object = &object_0056AF50;
	___SONIC_ACTIONS[23]->object = &object_0056AF50;
	___SONIC_ACTIONS[27]->object = &object_0056AF50;
	___SONIC_ACTIONS[28]->object = &object_0056AF50;
	___SONIC_ACTIONS[29]->object = &object_0056AF50;
	___SONIC_ACTIONS[30]->object = &object_0056AF50;
	___SONIC_ACTIONS[31]->object = &object_0056AF50;
	___SONIC_ACTIONS[32]->object = &object_0056AF50;
	___SONIC_ACTIONS[33]->object = &object_0056AF50;
	___SONIC_ACTIONS[34]->object = &object_0056AF50;
	___SONIC_ACTIONS[35]->object = &object_0056AF50;
	___SONIC_ACTIONS[36]->object = &object_0056AF50;
	___SONIC_ACTIONS[37]->object = &object_0056AF50;
	___SONIC_ACTIONS[38]->object = &object_0056AF50;
	___SONIC_ACTIONS[39]->object = &object_0056AF50;
	___SONIC_ACTIONS[40]->object = &object_0056AF50;
	___SONIC_ACTIONS[41]->object = &object_0056AF50;
	___SONIC_ACTIONS[42]->object = &object_0056AF50;
	___SONIC_ACTIONS[43]->object = &object_0056AF50;
	___SONIC_ACTIONS[44]->object = &object_0056AF50;
	___SONIC_ACTIONS[45]->object = &object_0056AF50;
	___SONIC_ACTIONS[46]->object = &object_0056AF50;
	___SONIC_ACTIONS[47]->object = &object_0056AF50;
	___SONIC_ACTIONS[48]->object = &object_0056AF50;
	___SONIC_ACTIONS[49]->object = &object_0056AF50;
	___SONIC_ACTIONS[50]->object = &object_0056AF50;
	___SONIC_ACTIONS[51]->object = &object_0056AF50;
	___SONIC_ACTIONS[52]->object = &object_0056AF50;
	___SONIC_ACTIONS[53]->object = &object_0056AF50;
	___SONIC_ACTIONS[54]->object = &object_0056AF50;
	___SONIC_ACTIONS[55]->object = &object_0056AF50;
	___SONIC_ACTIONS[56]->object = &object_0056AF50;
	___SONIC_ACTIONS[57]->object = &object_0056AF50;
	___SONIC_ACTIONS[58]->object = &object_0056AF50;
	___SONIC_ACTIONS[59]->object = &object_0056AF50;
	___SONIC_ACTIONS[60]->object = &object_0056AF50;
	___SONIC_ACTIONS[61]->object = &object_0056AF50;
	___SONIC_ACTIONS[62]->object = &object_0056AF50;
	___SONIC_ACTIONS[63]->object = &object_0056AF50;
	___SONIC_ACTIONS[64]->object = &object_0056AF50;
	___SONIC_ACTIONS[65]->object = &object_0056AF50;
	___SONIC_ACTIONS[66]->object = &object_0056AF50;
	___SONIC_ACTIONS[67]->object = &object_0056AF50;
	___SONIC_ACTIONS[68]->object = &object_0056AF50;
	___SONIC_ACTIONS[69]->object = &object_0056AF50;
	___SONIC_ACTIONS[70]->object = &object_0056AF50;
	___SONIC_ACTIONS[71]->object = &object_0056AF50;
	___SONIC_ACTIONS[72]->object = &object_0056AF50;
	___SONIC_ACTIONS[87]->object = &object_0056AF50;
	___SONIC_ACTIONS[88]->object = &object_0056AF50;
	___SONIC_ACTIONS[89]->object = &object_0056AF50;
	___SONIC_ACTIONS[90]->object = &object_0056AF50;
	___SONIC_ACTIONS[91]->object = &object_0056AF50;
	___SONIC_ACTIONS[92]->object = &object_0056AF50;
	___SONIC_ACTIONS[93]->object = &object_0056AF50;
	___SONIC_ACTIONS[94]->object = &object_0056AF50;
	___SONIC_ACTIONS[95]->object = &object_0056AF50;
	___SONIC_ACTIONS[96]->object = &object_0056AF50;
	___SONIC_ACTIONS[97]->object = &object_0056AF50;
	___SONIC_ACTIONS[98]->object = &object_0056AF50;
	___SONIC_ACTIONS[99]->object = &object_0056AF50;
	___SONIC_ACTIONS[100]->object = &object_0056AF50;
	___SONIC_ACTIONS[101]->object = &object_0056AF50;
	___SONIC_ACTIONS[102]->object = &object_0056AF50;
	___SONIC_ACTIONS[103]->object = &object_0056AF50;
	___SONIC_ACTIONS[104]->object = &object_0056AF50;
	___SONIC_ACTIONS[105]->object = &object_0056AF50;
	___SONIC_ACTIONS[106]->object = &object_0056AF50;
	___SONIC_ACTIONS[107]->object = &object_0056AF50;
	___SONIC_ACTIONS[108]->object = &object_0056AF50;
	___SONIC_ACTIONS[109]->object = &object_0056AF50;
	___SONIC_ACTIONS[113]->object = &object_0056AF50;
	___SONIC_ACTIONS[114]->object = &object_0056AF50;
	___SONIC_ACTIONS[115]->object = &object_0056AF50;
	___SONIC_ACTIONS[116]->object = &object_0056AF50;
	___SONIC_ACTIONS[117]->object = &object_0056AF50;
	___SONIC_ACTIONS[118]->object = &object_0056AF50;
	___SONIC_ACTIONS[119]->object = &object_0056AF50;
	___SONIC_ACTIONS[120]->object = &object_0056AF50;
	___SONIC_ACTIONS[121]->object = &object_0056AF50;
	___SONIC_ACTIONS[122]->object = &object_0056AF50;
	___SONIC_ACTIONS[123]->object = &object_0056AF50;
	___SONIC_ACTIONS[124]->object = &object_0056AF50;
	___SONIC_ACTIONS[125]->object = &object_0056AF50;
	___SONIC_ACTIONS[126]->object = &object_0056AF50;
	___SONIC_ACTIONS[127]->object = &object_0056AF50;
	___SONIC_ACTIONS[128]->object = &object_0056AF50;
	___SONIC_ACTIONS[129]->object = &object_0056AF50;
	___SONIC_ACTIONS[130]->object = &object_0062DE88;
	___SONIC_ACTIONS[131]->object = &object_0062DE88;
	___SONIC_ACTIONS[132]->object = &object_0062DE88;
	___SONIC_ACTIONS[133]->object = &object_0062DE88;
	___SONIC_ACTIONS[134]->object = &object_0056AF50;
	___SONIC_ACTIONS[135]->object = &object_0056AF50;
	___SONIC_ACTIONS[136]->object = &object_0056AF50;
	___SONIC_ACTIONS[137]->object = &object_0056AF50;
	___SONIC_ACTIONS[138]->object = &object_0062DE88;
	___SONIC_ACTIONS[139]->object = &object_0062DE88;
	___SONIC_ACTIONS[140]->object = &object_0062DE88;
	___SONIC_ACTIONS[141]->object = &object_0062DE88;
	___SONIC_ACTIONS[143]->object = &object_0062DE88;
	___SONIC_ACTIONS[144]->object = &object_0062DE88;
	___SONIC_ACTIONS[145]->object = &object_0056AF50;
	___SONIC_ACTIONS[146]->object = &object_0056AF50;
	___SONIC_ACTIONS[147]->object = &object_0056AF50;
	___SONIC_ACTIONS[148]->object = &object_0056AF50;
	___SONIC_MODELS[0] = &attach_0055F304;
	___SONIC_MODELS[1] = &attach_00560DA4;
	___SONIC_MODELS[2] = &attach_005735AC;
	___SONIC_MODELS[3] = &attach_00573DFC;
	___SONIC_MODELS[4] = &attach_0057464C;
	___SONIC_MODELS[5] = &attach_0057525C;
	___SONIC_MODELS[6] = &attach_00575AB4;
	___SONIC_MODELS[7] = &attach_0057630C;
	___SONIC_MODELS[8] = &attach_00569568;
	___SONIC_MODELS[9] = &attach_00579C68;
	___SONIC_MOTIONS[0] = &CinematicHead;

	//Tails Model Data
	ResizeTextureList((NJS_TEXLIST *)0x91A9C8, 24);
	NJS_OBJECT **___MILES_OBJECTS = (NJS_OBJECT **)GetProcAddress(handle, "___MILES_OBJECTS");
	MILES_OBJECTS = ___MILES_OBJECTS;
	NJS_ACTION **___MILES_ACTIONS = (NJS_ACTION **)GetProcAddress(handle, "___MILES_ACTIONS");
	MILES_ACTIONS = ___MILES_ACTIONS;
	NJS_MODEL_SADX **___MILES_MODELS = (NJS_MODEL_SADX **)GetProcAddress(handle, "___MILES_MODELS");
	MILES_MODELS = ___MILES_MODELS;
	NJS_MOTION **___MILES_MOTIONS = (NJS_MOTION **)GetProcAddress(handle, "___MILES_MOTIONS");
	MILES_MOTIONS = ___MILES_MOTIONS;
	___MILES_OBJECTS[0] = &object_0042AD54;
	___MILES_OBJECTS[1] = &object_00437C44;
	___MILES_OBJECTS[2] = &object_0043F4B4;
	___MILES_OBJECTS[3] = &object_0044148C;
	___MILES_OBJECTS[4] = &object_0042ABE8;
	___MILES_OBJECTS[5] = &object_00437AD8;
	___MILES_OBJECTS[6] = &object_0042AC84;
	___MILES_OBJECTS[7] = &object_00437B74;
	___MILES_OBJECTS[8] = &object_00426ED0;
	___MILES_OBJECTS[9] = &object_00426B90;
	___MILES_OBJECTS[10] = &object_00433DC0;
	___MILES_OBJECTS[11] = &object_00433A80;
	___MILES_OBJECTS[12] = &object_0041E548;
	___MILES_OBJECTS[13] = &object_0041EC90;
	___MILES_OBJECTS[14] = &object_0041ED2C;
	___MILES_OBJECTS[15] = &object_0041E5E4;
	___MILES_OBJECTS[16] = &object_0042BC1C;
	___MILES_OBJECTS[17] = &object_0042B4D4;
	___MILES_OBJECTS[18] = &object_0042BBE8;
	___MILES_OBJECTS[19] = &object_0042B4A0;
	___MILES_OBJECTS[20] = &object_00424D00;
	___MILES_OBJECTS[21] = &object_00424E94;
	___MILES_OBJECTS[22] = &object_0042674C;
	___MILES_OBJECTS[23] = &object_00422FD8;
	___MILES_OBJECTS[24] = &object_0042316C;
	___MILES_OBJECTS[25] = &object_00424A14;
	___MILES_OBJECTS[26] = &object_0042182C;
	___MILES_OBJECTS[27] = &object_004219BC;
	___MILES_OBJECTS[28] = &object_00422CF0;
	___MILES_OBJECTS[29] = &object_004200CC;
	___MILES_OBJECTS[30] = &object_0042025C;
	___MILES_OBJECTS[31] = &object_00421598;
	___MILES_OBJECTS[32] = &object_004225C8;
	___MILES_OBJECTS[33] = &object_00421FE4;
	___MILES_OBJECTS[34] = &object_00420E70;
	___MILES_OBJECTS[35] = &object_00420884;
	___MILES_OBJECTS[36] = &object_00425E88;
	___MILES_OBJECTS[37] = &object_00425C40;
	___MILES_OBJECTS[38] = &object_00424158;
	___MILES_OBJECTS[39] = &object_00423F10;
	___MILES_OBJECTS[40] = &object_00431BF0;
	___MILES_OBJECTS[41] = &object_00431D84;
	___MILES_OBJECTS[42] = &object_0043363C;
	___MILES_OBJECTS[43] = &object_0042FEC8;
	___MILES_OBJECTS[44] = &object_0043005C;
	___MILES_OBJECTS[45] = &object_00431904;
	___MILES_OBJECTS[46] = &object_0042E71C;
	___MILES_OBJECTS[47] = &object_0042E8AC;
	___MILES_OBJECTS[48] = &object_0042FBE0;
	___MILES_OBJECTS[49] = &object_0042CFBC;
	___MILES_OBJECTS[50] = &object_0042D14C;
	___MILES_OBJECTS[51] = &object_0042E488;
	___MILES_OBJECTS[52] = &object_0042F4B8;
	___MILES_OBJECTS[53] = &object_0042EED4;
	___MILES_OBJECTS[54] = &object_0042DD60;
	___MILES_OBJECTS[55] = &object_0042D774;
	___MILES_OBJECTS[56] = &object_00432D78;
	___MILES_OBJECTS[57] = &object_00432B30;
	___MILES_OBJECTS[58] = &object_00431048;
	___MILES_OBJECTS[59] = &object_00430E00;
	___MILES_OBJECTS[60] = &object_0046E63C;
	___MILES_OBJECTS[61] = &object_0046F46C;
	___MILES_OBJECTS[62] = &object_0041FE04;
	___MILES_OBJECTS[63] = &object_0042CCF4;
	___MILES_OBJECTS[64] = &object_0046EE44;
	___MILES_OBJECTS[65] = &object_0046FC84;
	___MILES_OBJECTS[66] = &object_0042AC1C;
	___MILES_OBJECTS[67] = &object_0042ABE8;
	___MILES_OBJECTS[68] = &object_00437B0C;
	___MILES_OBJECTS[69] = &object_00437AD8;
	___MILES_OBJECTS[70] = &object_0044C724;
	___MILES_ACTIONS[0]->object = &object_00437C44;
	___MILES_ACTIONS[1]->object = &object_00437C44;
	___MILES_ACTIONS[2]->object = &object_00437C44;
	___MILES_ACTIONS[3]->object = &object_00437C44;
	___MILES_ACTIONS[4]->object = &object_00437C44;
	___MILES_ACTIONS[5]->object = &object_00437C44;
	___MILES_ACTIONS[6]->object = &object_00437C44;
	___MILES_ACTIONS[7]->object = &object_00437C44;
	___MILES_ACTIONS[8]->object = &object_00437C44;
	___MILES_ACTIONS[9]->object = &object_00437C44;
	___MILES_ACTIONS[10]->object = &object_00437C44;
	___MILES_ACTIONS[11]->object = &object_0042AD54;
	___MILES_ACTIONS[12]->object = &object_0042AD54;
	___MILES_ACTIONS[13]->object = &object_0042AD54;
	___MILES_ACTIONS[14]->object = &object_0042AD54;
	___MILES_ACTIONS[15]->object = &object_0042AD54;
	___MILES_ACTIONS[16]->object = &object_0042AD54;
	___MILES_ACTIONS[17]->object = &object_00437C44;
	___MILES_ACTIONS[18]->object = &object_00437C44;
	___MILES_ACTIONS[19]->object = &object_00437C44;
	___MILES_ACTIONS[20]->object = &object_00437C44;
	___MILES_ACTIONS[21]->object = &object_0042AD54;
	___MILES_ACTIONS[22]->object = &object_0042AD54;
	___MILES_ACTIONS[23]->object = &object_0042AD54;
	___MILES_ACTIONS[24]->object = &object_0042AD54;
	___MILES_ACTIONS[25]->object = &object_0042AD54;
	___MILES_ACTIONS[26]->object = &object_0042AD54;
	___MILES_ACTIONS[27]->object = &object_0042AD54;
	___MILES_ACTIONS[28]->object = &object_0042AD54;
	___MILES_ACTIONS[29]->object = &object_0042AD54;
	___MILES_ACTIONS[30]->object = &object_0042AD54;
	___MILES_ACTIONS[31]->object = &object_0042AD54;
	___MILES_ACTIONS[32]->object = &object_0042AD54;
	___MILES_ACTIONS[33]->object = &object_0042AD54;
	___MILES_ACTIONS[34]->object = &object_0042AD54;
	___MILES_ACTIONS[35]->object = &object_0042AD54;
	___MILES_ACTIONS[36]->object = &object_0042AD54;
	___MILES_ACTIONS[37]->object = &object_0042AD54;
	___MILES_ACTIONS[38]->object = &object_0042AD54;
	___MILES_ACTIONS[39]->object = &object_0042AD54;
	___MILES_ACTIONS[40]->object = &object_0042AD54;
	___MILES_ACTIONS[41]->object = &object_0042AD54;
	___MILES_ACTIONS[42]->object = &object_0042AD54;
	___MILES_ACTIONS[43]->object = &object_0042AD54;
	___MILES_ACTIONS[44]->object = &object_0042AD54;
	___MILES_ACTIONS[45]->object = &object_0042AD54;
	___MILES_ACTIONS[46]->object = &object_0042AD54;
	___MILES_ACTIONS[47]->object = &object_0042AD54;
	___MILES_ACTIONS[48]->object = &object_0042AD54;
	___MILES_ACTIONS[49]->object = &object_0042AD54;
	___MILES_ACTIONS[50]->object = &object_0042AD54;
	___MILES_ACTIONS[51]->object = &object_0042AD54;
	___MILES_ACTIONS[52]->object = &object_0042AD54;
	___MILES_ACTIONS[53]->object = &object_00437C44;
	___MILES_ACTIONS[54]->object = &object_00437C44;
	___MILES_ACTIONS[55]->object = &object_0042AD54;
	___MILES_ACTIONS[56]->object = &object_0042AD54;
	___MILES_ACTIONS[57]->object = &object_0042AD54;
	___MILES_ACTIONS[58]->object = &object_0042AD54;
	___MILES_ACTIONS[59]->object = &object_0042AD54;
	___MILES_ACTIONS[60]->object = &object_0042AD54;
	___MILES_ACTIONS[61]->object = &object_0042AD54;
	___MILES_ACTIONS[62]->object = &object_0042AD54;
	___MILES_ACTIONS[63]->object = &object_0042AD54;
	___MILES_ACTIONS[64]->object = &object_0043F4B4;
	___MILES_ACTIONS[65]->object = &object_0044148C;
	___MILES_ACTIONS[66]->object = &object_0042AD54;
	___MILES_ACTIONS[67]->object = &object_0042AD54;
	___MILES_ACTIONS[68]->object = &object_0042AD54;
	___MILES_ACTIONS[69]->object = &object_0042AD54;
	___MILES_ACTIONS[70]->object = &object_0042AD54;
	___MILES_ACTIONS[71]->object = &object_0042AD54;
	___MILES_ACTIONS[72]->object = &object_0042AD54;
	___MILES_ACTIONS[73]->object = &object_0042AD54;
	___MILES_ACTIONS[74]->object = &object_0042AD54;
	___MILES_ACTIONS[75]->object = &object_0042AD54;
	___MILES_ACTIONS[76]->object = &object_0042AD54;
	___MILES_ACTIONS[77]->object = &object_0042AD54;
	___MILES_ACTIONS[78]->object = &object_0042AD54;
	___MILES_ACTIONS[79]->object = &object_0042AD54;
	___MILES_ACTIONS[80]->object = &object_0042AD54;
	___MILES_ACTIONS[81]->object = &object_0042AD54;
	___MILES_ACTIONS[82]->object = &object_0042AD54;
	___MILES_ACTIONS[83]->object = &object_0042AD54;
	___MILES_ACTIONS[85]->object = &object_0042AD54;
	___MILES_ACTIONS[86]->object = &object_0042AD54;
	___MILES_ACTIONS[87]->object = &object_0042AD54;
	___MILES_ACTIONS[88]->object = &object_0042AD54;
	___MILES_ACTIONS[91]->object = &object_0042AD54;
	___MILES_ACTIONS[92]->object = &object_0042AD54;
	___MILES_ACTIONS[93]->object = &object_0042AD54;
	___MILES_ACTIONS[94]->object = &object_0042AD54;
	___MILES_ACTIONS[95]->object = &object_0042AD54;
	___MILES_ACTIONS[96]->object = &object_0042AD54;
	___MILES_ACTIONS[97]->object = &object_0042AD54;
	___MILES_ACTIONS[110]->object = &object_0042AD54;
	___MILES_ACTIONS[111]->object = &object_0042AD54;
	___MILES_ACTIONS[112]->object = &object_0042AD54;
	___MILES_ACTIONS[113]->object = &object_0042AD54;
	___MILES_MODELS[0] = &attach_0041FDD8;
	___MILES_MODELS[1] = &attach_0042CCC8;
	___MILES_MODELS[2] = &attach_0042ABBC;
	___MILES_MODELS[3] = &attach_00437AAC;
	___MILES_MODELS[4] = &attach_0044517C;
	___MILES_MODELS[5] = &attach_0041E51C;
	___MILES_MODELS[6] = &attach_0041EC64;
	___MILES_MODELS[7] = &attach_0042B40C;
	___MILES_MODELS[8] = &attach_0042BB54;
	___MILES_MODELS[9] = &attach_00445778;
	___MILES_MODELS[10] = &attach_00445DA8;
	___MILES_MODELS[11] = &attach_00446A08;
	___MILES_MODELS[12] = &attach_00447038;
	___MILES_MODELS[13] = &attach_004463D8;
	___MILES_MODELS[14] = &attach_0046DFE8;
	___MILES_MOTIONS[0] = &TailsCinematicHead;

	//Knuckles
	ResizeTextureList((NJS_TEXLIST *)0x0091BD20, 22);
	NJS_OBJECT **___KNUCKLES_OBJECTS = (NJS_OBJECT **)GetProcAddress(handle, "___KNUCKLES_OBJECTS");
	KNUCKLES_OBJECTS = ___KNUCKLES_OBJECTS;
	NJS_ACTION **___KNUCKLES_ACTIONS = (NJS_ACTION **)GetProcAddress(handle, "___KNUCKLES_ACTIONS");
	KNUCKLES_ACTIONS = ___KNUCKLES_ACTIONS;
	NJS_MODEL_SADX **___KNUCKLES_MODELS = (NJS_MODEL_SADX **)GetProcAddress(handle, "___KNUCKLES_MODELS");
	KNUCKLES_MODELS = ___KNUCKLES_MODELS;
	NJS_MOTION **___KNUCKLES_MOTIONS = (NJS_MOTION **)GetProcAddress(handle, "___KNUCKLES_MOTIONS");
	KNUCKLES_MOTIONS = ___KNUCKLES_MOTIONS;
	___KNUCKLES_OBJECTS[0] = &object_002E23B0;
	___KNUCKLES_OBJECTS[1] = &object_002EEE50;
	___KNUCKLES_OBJECTS[2] = &object_002DB8A4;
	___KNUCKLES_OBJECTS[3] = &object_002DBA34;
	___KNUCKLES_OBJECTS[4] = &object_002DD0AC;
	___KNUCKLES_OBJECTS[5] = &object_002DC244;
	___KNUCKLES_OBJECTS[6] = &object_002D9E5C;
	___KNUCKLES_OBJECTS[7] = &object_002D9FEC;
	___KNUCKLES_OBJECTS[8] = &object_002DB5F4;
	___KNUCKLES_OBJECTS[9] = &object_002DAB34;
	___KNUCKLES_OBJECTS[10] = &object_002D876C;
	___KNUCKLES_OBJECTS[11] = &object_002D88FC;
	___KNUCKLES_OBJECTS[12] = &object_002D9BB0;
	___KNUCKLES_OBJECTS[13] = &object_002D6FE4;
	___KNUCKLES_OBJECTS[14] = &object_002D7174;
	___KNUCKLES_OBJECTS[15] = &object_002D8438;
	___KNUCKLES_OBJECTS[16] = &object_002D9754;
	___KNUCKLES_OBJECTS[17] = &object_002D9088;
	___KNUCKLES_OBJECTS[18] = &object_002D7FDC;
	___KNUCKLES_OBJECTS[19] = &object_002D7900;
	___KNUCKLES_OBJECTS[20] = &object_002DC94C;
	___KNUCKLES_OBJECTS[21] = &object_002DC244;
	___KNUCKLES_OBJECTS[22] = &object_002DAEE4;
	___KNUCKLES_OBJECTS[23] = &object_002DAB34;
	___KNUCKLES_OBJECTS[24] = &object_002E8324;
	___KNUCKLES_OBJECTS[25] = &object_002E84B4;
	___KNUCKLES_OBJECTS[26] = &object_002E9B2C;
	___KNUCKLES_OBJECTS[27] = &object_002E8CC4;
	___KNUCKLES_OBJECTS[28] = &object_002E68DC;
	___KNUCKLES_OBJECTS[29] = &object_002E6A6C;
	___KNUCKLES_OBJECTS[30] = &object_002E8074;
	___KNUCKLES_OBJECTS[31] = &object_002E75B4;
	___KNUCKLES_OBJECTS[32] = &object_002E51EC;
	___KNUCKLES_OBJECTS[33] = &object_002E537C;
	___KNUCKLES_OBJECTS[34] = &object_002E6630;
	___KNUCKLES_OBJECTS[35] = &object_002E3A64;
	___KNUCKLES_OBJECTS[36] = &object_002E3BF4;
	___KNUCKLES_OBJECTS[37] = &object_002E4EB8;
	___KNUCKLES_OBJECTS[38] = &object_002E61D4;
	___KNUCKLES_OBJECTS[39] = &object_002E5B08;
	___KNUCKLES_OBJECTS[40] = &object_002E4A5C;
	___KNUCKLES_OBJECTS[41] = &object_002E4380;
	___KNUCKLES_OBJECTS[42] = &object_002E93CC;
	___KNUCKLES_OBJECTS[43] = &object_002E8CC4;
	___KNUCKLES_OBJECTS[44] = &object_002E7964;
	___KNUCKLES_OBJECTS[45] = &object_002E75B4;
	___KNUCKLES_OBJECTS[46] = &object_00328878;
	___KNUCKLES_OBJECTS[47] = &object_003291C4;
	___KNUCKLES_OBJECTS[49] = &object_002E191C;
	___KNUCKLES_OBJECTS[50] = &object_002EE3BC;
	___KNUCKLES_OBJECTS[51] = &object_002E21A8;
	___KNUCKLES_OBJECTS[52] = &object_002E2070;
	___KNUCKLES_OBJECTS[53] = &object_002E1C78;
	___KNUCKLES_OBJECTS[54] = &object_002E1D14;
	___KNUCKLES_OBJECTS[55] = &object_002E191C;
	___KNUCKLES_OBJECTS[56] = &object_0030257C;
	___KNUCKLES_OBJECTS[58] = &object_002DB5F4;
	___KNUCKLES_OBJECTS[59] = &object_002DAEE4;
	___KNUCKLES_OBJECTS[60] = &object_002DAB34;
	___KNUCKLES_OBJECTS[61] = &object_002DA324;
	___KNUCKLES_OBJECTS[62] = &object_002DD0AC;
	___KNUCKLES_OBJECTS[63] = &object_002DC94C;
	___KNUCKLES_OBJECTS[64] = &object_002DC244;
	___KNUCKLES_OBJECTS[65] = &object_002DC59C;
	___KNUCKLES_OBJECTS[66] = &object_002E8074;
	___KNUCKLES_OBJECTS[67] = &object_002E7964;
	___KNUCKLES_OBJECTS[68] = &object_002E75B4;
	___KNUCKLES_OBJECTS[69] = &object_002E6DA4;
	___KNUCKLES_OBJECTS[70] = &object_002E9B2C;
	___KNUCKLES_OBJECTS[71] = &object_002E93CC;
	___KNUCKLES_OBJECTS[72] = &object_002E8CC4;
	___KNUCKLES_OBJECTS[73] = &object_002E901C;
	___KNUCKLES_ACTIONS[0]->object = &object_002E23B0;
	___KNUCKLES_ACTIONS[1]->object = &object_002E23B0;
	___KNUCKLES_ACTIONS[2]->object = &object_002EEE50;
	___KNUCKLES_ACTIONS[3]->object = &object_002EEE50;
	___KNUCKLES_ACTIONS[4]->object = &object_002EEE50;
	___KNUCKLES_ACTIONS[5]->object = &object_002EEE50;
	___KNUCKLES_ACTIONS[6]->object = &object_002E23B0;
	___KNUCKLES_ACTIONS[7]->object = &object_002EEE50;
	___KNUCKLES_ACTIONS[9]->object = &object_002E23B0;
	___KNUCKLES_ACTIONS[10]->object = &object_002E23B0;
	___KNUCKLES_ACTIONS[11]->object = &object_002E23B0;
	___KNUCKLES_ACTIONS[12]->object = &object_002E23B0;
	___KNUCKLES_ACTIONS[13]->object = &object_002E23B0;
	___KNUCKLES_ACTIONS[14]->object = &object_002E23B0;
	___KNUCKLES_ACTIONS[15]->object = &object_002EEE50;
	___KNUCKLES_ACTIONS[16]->object = &object_002EEE50;
	___KNUCKLES_ACTIONS[17]->object = &object_002EEE50;
	___KNUCKLES_ACTIONS[18]->object = &object_002EEE50;
	___KNUCKLES_ACTIONS[19]->object = &object_002EEE50;
	___KNUCKLES_ACTIONS[20]->object = &object_002EEE50;
	___KNUCKLES_ACTIONS[21]->object = &object_002EEE50;
	___KNUCKLES_ACTIONS[22]->object = &object_002E23B0;
	___KNUCKLES_ACTIONS[23]->object = &object_002E23B0;
	___KNUCKLES_ACTIONS[24]->object = &object_002E23B0;
	___KNUCKLES_ACTIONS[25]->object = &object_002E23B0;
	___KNUCKLES_ACTIONS[26]->object = &object_002E23B0;
	___KNUCKLES_ACTIONS[27]->object = &object_002E23B0;
	___KNUCKLES_ACTIONS[28]->object = &object_002E23B0;
	___KNUCKLES_ACTIONS[29]->object = &object_002E23B0;
	___KNUCKLES_ACTIONS[30]->object = &object_002E23B0;
	___KNUCKLES_ACTIONS[31]->object = &object_002E23B0;
	___KNUCKLES_ACTIONS[32]->object = &object_002E23B0;
	___KNUCKLES_ACTIONS[33]->object = &object_002E23B0;
	___KNUCKLES_ACTIONS[34]->object = &object_002E23B0;
	___KNUCKLES_ACTIONS[35]->object = &object_002EEE50;
	___KNUCKLES_ACTIONS[36]->object = &object_002EEE50;
	___KNUCKLES_ACTIONS[37]->object = &object_002EEE50;
	___KNUCKLES_ACTIONS[38]->object = &object_002E23B0;
	___KNUCKLES_ACTIONS[39]->object = &object_002EEE50;
	___KNUCKLES_ACTIONS[40]->object = &object_002E23B0;
	___KNUCKLES_ACTIONS[41]->object = &object_002E23B0;
	___KNUCKLES_ACTIONS[42]->object = &object_002EEE50;
	___KNUCKLES_ACTIONS[43]->object = &object_002E23B0;
	___KNUCKLES_ACTIONS[44]->object = &object_002E23B0;
	___KNUCKLES_ACTIONS[45]->object = &object_002E23B0;
	___KNUCKLES_ACTIONS[46]->object = &object_002E23B0;
	___KNUCKLES_ACTIONS[47]->object = &object_002E23B0;
	___KNUCKLES_ACTIONS[48]->object = &object_002E23B0;
	___KNUCKLES_ACTIONS[49]->object = &object_002E23B0;
	___KNUCKLES_ACTIONS[50]->object = &object_002E23B0;
	___KNUCKLES_ACTIONS[51]->object = &object_002E23B0;
	___KNUCKLES_ACTIONS[52]->object = &object_002EEE50;
	___KNUCKLES_ACTIONS[53]->object = &object_002E23B0;
	___KNUCKLES_ACTIONS[54]->object = &object_002E23B0;
	___KNUCKLES_ACTIONS[55]->object = &object_002E23B0;
	___KNUCKLES_ACTIONS[56]->object = &object_002E23B0;
	___KNUCKLES_ACTIONS[57]->object = &object_002EEE50;
	___KNUCKLES_ACTIONS[58]->object = &object_002E23B0;
	___KNUCKLES_ACTIONS[59]->object = &object_002E23B0;
	___KNUCKLES_ACTIONS[60]->object = &object_002E23B0;
	___KNUCKLES_ACTIONS[61]->object = &object_002F8530;
	___KNUCKLES_ACTIONS[62]->object = &object_002F0E24;
	___KNUCKLES_ACTIONS[63]->object = &object_002E23B0;
	___KNUCKLES_ACTIONS[64]->object = &object_002E23B0;
	___KNUCKLES_ACTIONS[65]->object = &object_002E23B0;
	___KNUCKLES_ACTIONS[66]->object = &object_002E23B0;
	___KNUCKLES_ACTIONS[67]->object = &object_002E23B0;
	___KNUCKLES_ACTIONS[68]->object = &object_002E23B0;
	___KNUCKLES_ACTIONS[69]->object = &object_002E23B0;
	___KNUCKLES_ACTIONS[70]->object = &object_002E23B0;
	___KNUCKLES_ACTIONS[71]->object = &object_002E23B0;
	___KNUCKLES_ACTIONS[72]->object = &object_002E23B0;
	___KNUCKLES_ACTIONS[73]->object = &object_002E23B0;
	___KNUCKLES_ACTIONS[74]->object = &object_002E23B0;
	___KNUCKLES_ACTIONS[75]->object = &object_002E23B0;
	___KNUCKLES_ACTIONS[76]->object = &object_002E23B0;
	___KNUCKLES_ACTIONS[77]->object = &object_002E23B0;
	___KNUCKLES_ACTIONS[78]->object = &object_002E23B0;
	___KNUCKLES_ACTIONS[79]->object = &object_002E23B0;
	___KNUCKLES_ACTIONS[80]->object = &object_002E23B0;
	___KNUCKLES_ACTIONS[81]->object = &object_002E23B0;
	___KNUCKLES_ACTIONS[82]->object = &object_002E23B0;
	___KNUCKLES_ACTIONS[83]->object = &object_002E23B0;
	___KNUCKLES_ACTIONS[84]->object = &object_002E23B0;
	___KNUCKLES_ACTIONS[85]->object = &object_002EEE50;
	___KNUCKLES_ACTIONS[86]->object = &object_002E23B0;
	___KNUCKLES_ACTIONS[87]->object = &object_002E23B0;
	___KNUCKLES_ACTIONS[88]->object = &object_002E23B0;
	___KNUCKLES_ACTIONS[89]->object = &object_002E23B0;
	___KNUCKLES_MODELS[0] = &attach_003298C8;
	___KNUCKLES_MODELS[1] = &attach_00329FF8;
	___KNUCKLES_MODELS[2] = &attach_0032A6F0;
	___KNUCKLES_MODELS[3] = &attach_0032ADF8;
	___KNUCKLES_MODELS[4] = &attach_002E18F0;
	___KNUCKLES_MODELS[5] = &attach_002EE390;
	___KNUCKLES_MODELS[6] = &attach_002FC558;
	___KNUCKLES_MODELS[7] = &attach_002DB5C8;
	___KNUCKLES_MODELS[8] = &attach_002DAEB8;
	___KNUCKLES_MODELS[9] = &attach_002DAB08;
	___KNUCKLES_MODELS[10] = &attach_002DA2F8;
	___KNUCKLES_MODELS[11] = &attach_002DD080;
	___KNUCKLES_MODELS[12] = &attach_002DC920;
	___KNUCKLES_MODELS[13] = &attach_002DC218;
	___KNUCKLES_MODELS[14] = &attach_002DC570;
	___KNUCKLES_MODELS[15] = &attach_0032C950;
	___KNUCKLES_MODELS[16] = &attach_0032C2F8;
	___KNUCKLES_MODELS[17] = &attach_0032BF48;
	___KNUCKLES_MODELS[18] = &attach_0032B7C0;
	___KNUCKLES_MODELS[19] = &attach_0032B488;
	___KNUCKLES_MODELS[20] = &attach_0032D7E0;
	___KNUCKLES_MODELS[21] = &attach_0032D430;
	___KNUCKLES_MODELS[22] = &attach_0032CCA8;
	___KNUCKLES_MOTIONS[0] = &KnucklesEV;

	//Amy
	ResizeTextureList((NJS_TEXLIST *)0x0091C800, 53);
	NJS_OBJECT **___AMY_OBJECTS = (NJS_OBJECT **)GetProcAddress(handle, "___AMY_OBJECTS");
	AMY_OBJECTS = ___AMY_OBJECTS;
	NJS_ACTION **___AMY_ACTIONS = (NJS_ACTION **)GetProcAddress(handle, "___AMY_ACTIONS");
	NJS_MODEL_SADX **___AMY_MODELS = (NJS_MODEL_SADX **)GetProcAddress(handle, "___AMY_MODELS");
	AMY_MODELS = ___AMY_MODELS;
	NJS_MOTION **___AMY_MOTIONS = (NJS_MOTION **)GetProcAddress(handle, "___AMY_MOTIONS");
	___AMY_OBJECTS[0] = &object_00016460;
	//___AMY_OBJECTS[1] = &object_00016E7C;
	___AMY_OBJECTS[2] = &object_0000FB34;
	___AMY_OBJECTS[3] = &object_0000F974;
	___AMY_OBJECTS[4] = &object_000159CC;
	___AMY_OBJECTS[5] = &object_00009C54;
	___AMY_OBJECTS[6] = &object_0000EA74;
	___AMY_OBJECTS[7] = &object_0000EC04;
	___AMY_OBJECTS[8] = &object_000112C4;
	___AMY_OBJECTS[9] = &object_0000CE6C;
	___AMY_OBJECTS[10] = &object_0000CFFC;
	___AMY_OBJECTS[11] = &object_0000D7B4;
	___AMY_OBJECTS[12] = &object_0000B7D4;
	___AMY_OBJECTS[13] = &object_0000B994;
	___AMY_OBJECTS[14] = &object_0000CBC0;
	___AMY_OBJECTS[15] = &object_0000A114;
	___AMY_OBJECTS[16] = &object_0000A2D4;
	___AMY_OBJECTS[17] = &object_0000B510;
	___AMY_OBJECTS[18] = &object_0000C508;
	___AMY_OBJECTS[19] = &object_0000BE90;
	___AMY_OBJECTS[20] = &object_0000AE48;
	___AMY_OBJECTS[21] = &object_0000A7D0;
	___AMY_OBJECTS[22] = &object_00010AF8;
	___AMY_OBJECTS[23] = &object_000108A0;
	___AMY_OBJECTS[24] = &object_0000E7C8;
	___AMY_OBJECTS[25] = &object_0000E570;
	___AMY_OBJECTS[26] = &object_00016258;
	___AMY_OBJECTS[27] = &object_00016120;
	___AMY_OBJECTS[28] = &object_00015D28;
	___AMY_OBJECTS[30] = &object_00015DC4;
	___AMY_OBJECTS[31] = &object_000159CC;
	___AMY_OBJECTS[32] = &object_00023300;
	___AMY_OBJECTS[33] = &object_000159CC;
	___AMY_OBJECTS[34] = &object_00012324;
	___AMY_OBJECTS[35] = &object_0001D858;
	___AMY_OBJECTS[36] = &object_0000FDF8;
	___AMY_OBJECTS[37] = &object_0000FB34;
	___AMY_OBJECTS[38] = &object_0001D204;
	___AMY_ACTIONS[0]->object = &object_00016460;
	___AMY_ACTIONS[1]->object = &object_00016460;
	___AMY_ACTIONS[2]->object = &object_00016460;
	___AMY_ACTIONS[3]->object = &object_00016460;
	___AMY_ACTIONS[4]->object = &object_00016460;
	___AMY_ACTIONS[5]->object = &object_00016460;
	___AMY_ACTIONS[6]->object = &object_00016460;
	___AMY_ACTIONS[7]->object = &object_00016460;
	___AMY_ACTIONS[8]->object = &object_00016460;
	___AMY_ACTIONS[9]->object = &object_00016460;
	___AMY_ACTIONS[10]->object = &object_00016460;
	___AMY_ACTIONS[11]->object = &object_00016460;
	___AMY_ACTIONS[12]->object = &object_00016460;
	___AMY_ACTIONS[13]->object = &object_00016460;
	___AMY_ACTIONS[14]->object = &object_00016460;
	___AMY_ACTIONS[15]->object = &object_00016460;
	___AMY_ACTIONS[16]->object = &object_00016460;
	___AMY_ACTIONS[17]->object = &object_00016460;
	___AMY_ACTIONS[18]->object = &object_00016460;
	___AMY_ACTIONS[19]->object = &object_00016460;
	___AMY_ACTIONS[20]->object = &object_00016460;
	___AMY_ACTIONS[21]->object = &object_00016460;
	___AMY_ACTIONS[22]->object = &object_00016460;
	___AMY_ACTIONS[23]->object = &object_00016460;
	___AMY_ACTIONS[24]->object = &object_00016460;
	___AMY_ACTIONS[25]->object = &object_00016460;
	___AMY_ACTIONS[26]->object = &object_00016460;
	___AMY_ACTIONS[27]->object = &object_00016460;
	___AMY_ACTIONS[28]->object = &object_00016460;
	___AMY_ACTIONS[29]->object = &object_00016460;
	___AMY_ACTIONS[30]->object = &object_00016460;
	___AMY_ACTIONS[31]->object = &object_00016460;
	___AMY_ACTIONS[32]->object = &object_00016460;
	___AMY_ACTIONS[33]->object = &object_00016460;
	___AMY_ACTIONS[34]->object = &object_00016460;
	___AMY_ACTIONS[35]->object = &object_00016460;
	___AMY_ACTIONS[36]->object = &object_00016460;
	___AMY_ACTIONS[37]->object = &object_00016460;
	___AMY_ACTIONS[38]->object = &object_00016460;
	___AMY_ACTIONS[39]->object = &object_00016460;
	___AMY_ACTIONS[40]->object = &object_00016460;
	___AMY_ACTIONS[41]->object = &object_00016460;
	___AMY_ACTIONS[42]->object = &object_00016460;
	___AMY_ACTIONS[43]->object = &object_00016460;
	___AMY_ACTIONS[44]->object = &object_00016460;
	___AMY_ACTIONS[45]->object = &object_00016460;
	___AMY_ACTIONS[46]->object = &object_00016460;
	___AMY_ACTIONS[47]->object = &object_00016460;
	___AMY_ACTIONS[48]->object = &object_00016460;
	___AMY_ACTIONS[49]->object = &object_00016460;
	___AMY_ACTIONS[50]->object = &object_00016460;
	___AMY_ACTIONS[51]->object = &object_00016460;
	___AMY_ACTIONS[52]->object = &object_00016460;
	___AMY_ACTIONS[53]->object = &object_00016460;
	___AMY_ACTIONS[54]->object = &object_00016460;
	___AMY_ACTIONS[55]->object = &object_00016460;
	___AMY_ACTIONS[56]->object = &object_00016460;
	___AMY_ACTIONS[57]->object = &object_00016460;
	___AMY_ACTIONS[58]->object = &object_00016460;
	___AMY_ACTIONS[59]->object = &object_00016460;
	___AMY_ACTIONS[60]->object = &object_00016460;
	___AMY_ACTIONS[61]->object = &object_00016460;
	___AMY_ACTIONS[62]->object = &object_00016460;
	___AMY_ACTIONS[63]->object = &object_00016460;
	___AMY_ACTIONS[64]->object = &object_00016460;
	___AMY_ACTIONS[65]->object = &object_00016460;
	___AMY_ACTIONS[66]->object = &object_00016460;
	___AMY_ACTIONS[67]->object = &object_00016460;
	___AMY_ACTIONS[68]->object = &object_00016460;
	___AMY_ACTIONS[69]->object = &object_00016460;
	___AMY_ACTIONS[70]->object = &object_00016460;
	___AMY_ACTIONS[71]->object = &object_00016460;
	___AMY_ACTIONS[72]->object = &object_00016460;
	___AMY_ACTIONS[73]->object = &object_00016460;
	___AMY_ACTIONS[74]->object = &object_00016E7C;
	___AMY_ACTIONS[75]->object = &object_00016E7C;
	___AMY_ACTIONS[76]->object = &object_00016460;
	___AMY_ACTIONS[77]->object = &object_00016460;
	___AMY_ACTIONS[78]->object = &object_00016460;
	___AMY_ACTIONS[79]->object = &object_00016460;
	___AMY_MODELS[0] = &attach_00016DE8;
	___AMY_MODELS[1] = &attach_000159A0;
	___AMY_MODELS[2] = &attach_0001C100;
	___AMY_MODELS[3] = &attach_00009C28;
	___AMY_MODELS[4] = &attach_00018A90;
	___AMY_MOTIONS[0] = &AmyEVHead_Motion;
	WriteData((NJS_OBJECT**)0x009858A4, &object_00584EE0);

	//Big
	NJS_OBJECT **___BIG_OBJECTS = (NJS_OBJECT **)GetProcAddress(handle, "___BIG_OBJECTS");
	BIG_OBJECTS = ___BIG_OBJECTS;
	NJS_ACTION **___BIG_ACTIONS = (NJS_ACTION **)GetProcAddress(handle, "___BIG_ACTIONS");
	NJS_MODEL_SADX **___BIG_MODELS = (NJS_MODEL_SADX **)GetProcAddress(handle, "___BIG_MODELS");
	NJS_MOTION **___BIG_MOTIONS = (NJS_MOTION **)GetProcAddress(handle, "___BIG_MOTIONS");
	___BIG_OBJECTS[0] = &object_0012541C;
	___BIG_OBJECTS[1] = &object_0012CA3C;
	___BIG_OBJECTS[2] = &object_00120834;
	___BIG_OBJECTS[3] = &object_00120C14;
	___BIG_OBJECTS[4] = &object_0012210C;
	___BIG_OBJECTS[5] = &object_00121910;
	___BIG_OBJECTS[6] = &object_0011DD6C;
	___BIG_OBJECTS[7] = &object_0011E14C;
	___BIG_OBJECTS[8] = &object_0011E6E4;
	___BIG_OBJECTS[9] = &object_00120088;
	___BIG_OBJECTS[10] = &object_001233D4;
	___BIG_OBJECTS[11] = &object_0012414C;
	___BIG_OBJECTS[12] = &object_00123EA0;
	___BIG_OBJECTS[13] = &object_001239B4;
	___BIG_OBJECTS[14] = &object_0012450C;
	___BIG_OBJECTS[15] = &object_001247B4;
	___BIG_OBJECTS[16] = &object_001252B0;
	___BIG_OBJECTS[17] = &object_00124DBC;
	___BIG_OBJECTS[18] = &object_00121B8C;
	___BIG_OBJECTS[19] = &object_001291D4;
	___BIG_OBJECTS[20] = &object_00120304;
	___BIG_OBJECTS[22] = &object_0011D7A0;
	___BIG_OBJECTS[23] = &object_0011B5FC;
	___BIG_OBJECTS[24] = &object_0011B754;
	___BIG_OBJECTS[25] = &object_0011F384;
	___BIG_OBJECTS[26] = &object_0011D76C;
	___BIG_OBJECTS[27] = &object_0011D448;
	___BIG_OBJECTS[28] = &object_0012CA3C;
	___BIG_OBJECTS[30] = &object_001291D4;
	___BIG_OBJECTS[31] = &object_001284BC;
	___BIG_OBJECTS[32] = &object_0011B0D0;
	___BIG_OBJECTS[33] = &object_0011D808;
	___BIG_OBJECTS[34] = &object_0011F384;
	___BIG_OBJECTS[35] = &object_0011EC34;
	___BIG_OBJECTS[36] = &object_00128A90;
	___BIG_ACTIONS[0]->object = &object_0012541C;
	___BIG_ACTIONS[1]->object = &object_0012541C;
	___BIG_ACTIONS[2]->object = &object_0012541C;
	___BIG_ACTIONS[4]->object = &object_0012541C;
	___BIG_ACTIONS[5]->object = &object_0012541C;
	___BIG_ACTIONS[6]->object = &object_0012541C;
	___BIG_ACTIONS[7]->object = &object_0012541C;
	___BIG_ACTIONS[8]->object = &object_0012541C;
	___BIG_ACTIONS[9]->object = &object_0012541C;
	___BIG_ACTIONS[10]->object = &object_0012541C;
	___BIG_ACTIONS[11]->object = &object_0012541C;
	___BIG_ACTIONS[12]->object = &object_0012541C;
	___BIG_ACTIONS[13]->object = &object_0012541C;
	___BIG_ACTIONS[14]->object = &object_0012541C;
	___BIG_ACTIONS[15]->object = &object_0012541C;
	___BIG_ACTIONS[16]->object = &object_0012541C;
	___BIG_ACTIONS[17]->object = &object_0012541C;
	___BIG_ACTIONS[18]->object = &object_0012541C;
	___BIG_ACTIONS[19]->object = &object_0012541C;
	___BIG_ACTIONS[20]->object = &object_0012541C;
	___BIG_ACTIONS[21]->object = &object_0012541C;
	___BIG_ACTIONS[22]->object = &object_0012541C;
	___BIG_ACTIONS[23]->object = &object_0012541C;
	___BIG_ACTIONS[24]->object = &object_0012541C;
	___BIG_ACTIONS[25]->object = &object_0012541C;
	___BIG_ACTIONS[27]->object = &object_0012541C;
	___BIG_ACTIONS[28]->object = &object_0012541C;
	___BIG_ACTIONS[29]->object = &object_0012541C;
	___BIG_ACTIONS[30]->object = &object_0012541C;
	___BIG_ACTIONS[31]->object = &object_0012541C;
	___BIG_ACTIONS[32]->object = &object_0012541C;
	___BIG_ACTIONS[33]->object = &object_0012541C;
	___BIG_ACTIONS[34]->object = &object_0012541C;
	___BIG_ACTIONS[35]->object = &object_0012541C;
	___BIG_ACTIONS[36]->object = &object_0012541C;
	___BIG_ACTIONS[37]->object = &object_0012541C;
	___BIG_ACTIONS[38]->object = &object_0012541C;
	___BIG_ACTIONS[39]->object = &object_0012541C;
	___BIG_ACTIONS[40]->object = &object_0012541C;
	___BIG_ACTIONS[41]->object = &object_0012541C;
	___BIG_ACTIONS[42]->object = &object_0012541C;
	___BIG_ACTIONS[43]->object = &object_0012541C;
	___BIG_ACTIONS[44]->object = &object_0012541C;
	___BIG_ACTIONS[45]->object = &object_0012541C;
	___BIG_ACTIONS[46]->object = &object_0012541C;
	___BIG_ACTIONS[48]->object = &object_0012541C;
	___BIG_ACTIONS[55]->object = &object_0012541C;
	___BIG_ACTIONS[56]->object = &object_0012541C;
	___BIG_ACTIONS[57]->object = &object_0012541C;
	___BIG_ACTIONS[58]->object = &object_0012541C;
	___BIG_ACTIONS[59]->object = &object_0012541C;
	___BIG_ACTIONS[60]->object = &object_0012541C;
	___BIG_ACTIONS[61]->object = &object_0012541C;
	___BIG_ACTIONS[62]->object = &object_0012541C;
	___BIG_ACTIONS[63]->object = &object_0012541C;
	___BIG_ACTIONS[64]->object = &object_0012541C;
	___BIG_ACTIONS[65]->object = &object_0012541C;
	___BIG_ACTIONS[66]->object = &object_0012541C;
	___BIG_ACTIONS[67]->object = &object_0012541C;
	___BIG_ACTIONS[68]->object = &object_0012541C;
	___BIG_ACTIONS[69]->object = &object_0012541C;
	___BIG_ACTIONS[70]->object = &object_0012541C;
	___BIG_ACTIONS[72]->object = &object_0012541C;
	___BIG_ACTIONS[73]->object = &object_0012541C;
	___BIG_ACTIONS[74]->object = &object_0012541C;
	___BIG_ACTIONS[75]->object = &object_0012541C;
	___BIG_ACTIONS[76]->object = &object_0012541C;
	___BIG_ACTIONS[77]->object = &object_0012541C;
	___BIG_ACTIONS[78]->object = &object_0012541C;
	___BIG_ACTIONS[79]->object = &object_0012541C;
	___BIG_ACTIONS[80]->object = &object_0012541C;
	___BIG_ACTIONS[81]->object = &object_0012541C;
	___BIG_ACTIONS[82]->object = &object_0012541C;
	___BIG_ACTIONS[86]->object = &object_0012541C;
	___BIG_ACTIONS[87]->object = &object_0012541C;
	___BIG_ACTIONS[88]->object = &object_0012541C;
	___BIG_ACTIONS[89]->object = &object_0012541C;
	___BIG_MODELS[0] = &attach_0011D41C;
	___BIG_MODELS[1] = &attach_00126D14;
	___BIG_MODELS[2] = &attach_0011F358;
	___BIG_MODELS[3] = &attach_001291A8;
	___BIG_MOTIONS[0] = &BigEV_Motion;

	//Gamma
	NJS_OBJECT **___E102_OBJECTS = (NJS_OBJECT **)GetProcAddress(handle, "___E102_OBJECTS");
	NJS_ACTION **___E102_ACTIONS = (NJS_ACTION **)GetProcAddress(handle, "___E102_ACTIONS");
	___E102_OBJECTS[0] = &object_00207290;
	___E102_OBJECTS[7] = &object_00202C9C;
	___E102_OBJECTS[8] = &object_00202F8C;
	___E102_OBJECTS[9] = &object_002037EC;
	___E102_OBJECTS[10] = &object_0020323C;
	___E102_OBJECTS[11] = &object_00203820;
	___E102_OBJECTS[12] = &object_00201AE4;
	___E102_OBJECTS[22] = &object_00203820;
	___E102_OBJECTS[24] = &object_0020323C;
	___E102_OBJECTS[25] = &object_00202744;
	___E102_OBJECTS[26] = &object_00205CC8;
	___E102_OBJECTS[27] = &object_002070F0;
	___E102_ACTIONS[0]->object = &object_00207290;
	___E102_ACTIONS[1]->object = &object_00207290;
	___E102_ACTIONS[2]->object = &object_00207290;
	___E102_ACTIONS[3]->object = &object_00207290;
	___E102_ACTIONS[4]->object = &object_00207290;
	___E102_ACTIONS[5]->object = &object_00207290;
	___E102_ACTIONS[6]->object = &object_00207290;
	___E102_ACTIONS[13]->object = &object_00207290;
	___E102_ACTIONS[14]->object = &object_00207290;
	___E102_ACTIONS[15]->object = &object_00207290;
	___E102_ACTIONS[16]->object = &object_00207290;
	___E102_ACTIONS[17]->object = &object_00207290;
	___E102_ACTIONS[18]->object = &object_00207290;
	___E102_ACTIONS[19]->object = &object_00207290;
	___E102_ACTIONS[20]->object = &object_00207290;
	___E102_ACTIONS[21]->object = &object_00207290;
	___E102_ACTIONS[22]->object = &object_00207290;
	___E102_ACTIONS[23]->object = &object_00207290;
	___E102_ACTIONS[24]->object = &object_00207290;
	___E102_ACTIONS[25]->object = &object_00207290;
	___E102_ACTIONS[26]->object = &object_00207290;
	___E102_ACTIONS[27]->object = &object_00207290;
	___E102_ACTIONS[28]->object = &object_00207290;
	___E102_ACTIONS[29]->object = &object_00207290;
	___E102_ACTIONS[30]->object = &object_00207290;
	___E102_ACTIONS[31]->object = &object_00207290;
	___E102_ACTIONS[32]->object = &object_00207290;
	___E102_ACTIONS[33]->object = &object_00207290;
	___E102_ACTIONS[34]->object = &object_00207290;
	___E102_ACTIONS[35]->object = &object_00207290;
	___E102_ACTIONS[36]->object = &object_00207290;
	___E102_ACTIONS[37]->object = &object_00207290;
	___E102_ACTIONS[38]->object = &object_00207290;
	___E102_ACTIONS[39]->object = &object_00207290;
	___E102_ACTIONS[40]->object = &object_00207290;
	___E102_ACTIONS[41]->object = &object_00207290;
	___E102_ACTIONS[42]->object = &object_00207290;
	___E102_ACTIONS[43]->object = &object_00207290;
	___E102_ACTIONS[44]->object = &object_00207290;
	___E102_ACTIONS[45]->object = &object_00207290;
	___E102_ACTIONS[46]->object = &object_00207290;
	___E102_ACTIONS[47]->object = &object_00207290;
	___E102_ACTIONS[48]->object = &object_00207290;
	___E102_ACTIONS[49]->object = &object_00207290;
	___E102_ACTIONS[51]->object = &object_00207290;
	___E102_ACTIONS[52]->object = &object_00207290;
	___E102_ACTIONS[53]->object = &object_00207290;
	___E102_ACTIONS[54]->object = &object_00207290;
	___E102_ACTIONS[55]->object = &object_00207290;
	___E102_ACTIONS[56]->object = &object_00207290;
	___E102_ACTIONS[57]->object = &object_00207290;
	___E102_ACTIONS[58]->object = &object_00207290;
	___E102_ACTIONS[59]->object = &object_00207290;
	___E102_ACTIONS[60]->object = &object_00207290;
	___E102_ACTIONS[62]->object = &object_00207290;
	___E102_ACTIONS[63]->object = &object_00207290;
	___E102_ACTIONS[64]->object = &object_00207290;
	___E102_ACTIONS[65]->object = &object_00207290;
	___E102_ACTIONS[66]->object = &object_00207290;
	___E102_ACTIONS[67]->object = &object_00207290;
	___E102_ACTIONS[68]->object = &object_00207290;
	___E102_ACTIONS[69]->object = &object_00207290;
	___E102_ACTIONS[70]->object = &object_00207290;
	___E102_ACTIONS[71]->object = &object_00207290;
	___E102_ACTIONS[72]->object = &object_00207290;
	___E102_ACTIONS[73]->object = &object_00207290;
	___E102_ACTIONS[74]->object = &object_00207290;
	___E102_ACTIONS[75]->object = &object_00207290;
	___E102_ACTIONS[76]->object = &object_00207290;
	___E102_ACTIONS[77]->object = &object_00207290;

	//Tikal
	WriteData((NJS_OBJECT**)0x008F46BC, &Tikal_Object);
	WriteData((NJS_OBJECT**)0x008F83F4, &Tikal_Object);
	WriteData((NJS_OBJECT**)0x008FC8DC, &Tikal_Object);
	WriteData((NJS_OBJECT**)0x00900814, &Tikal_Object);
	WriteData((NJS_OBJECT**)0x02C81AA4, &Tikal_Object);
	WriteData((NJS_OBJECT**)0x02C8B13C, &Tikal_Object);
	WriteData((NJS_OBJECT**)0x02D4B2DC, &Tikal_Object);
	WriteData((NJS_OBJECT**)0x02D53284, &Tikal_Object);
	WriteData((NJS_OBJECT**)0x02D5C1FC, &Tikal_Object);
	WriteData((NJS_OBJECT**)0x02D61174, &Tikal_Object);
	WriteData((NJS_OBJECT**)0x02EAF60C, &Tikal_Object);
	WriteData((NJS_OBJECT**)0x02EB25F4, &Tikal_Object);
	WriteData((NJS_OBJECT**)0x02EBACB4, &Tikal_Object);
	WriteData((NJS_OBJECT**)0x02EBF89C, &Tikal_Object);
	WriteData((NJS_OBJECT**)0x02EC2524, &Tikal_Object);
	WriteData((NJS_OBJECT**)0x02ECD67C, &Tikal_Object);
	WriteData((NJS_OBJECT**)0x02ED7EA4, &Tikal_Object);
	WriteData((NJS_OBJECT**)0x02EDBE6C, &Tikal_Object);
	WriteData((NJS_OBJECT**)0x02EE08F4, &Tikal_Object);
	WriteData((NJS_OBJECT**)0x02F12A34, &Tikal_Object);
	WriteData((NJS_OBJECT**)0x02F1694C, &Tikal_Object);
	WriteData((NJS_OBJECT**)0x02F180B4, &Tikal_Object);
	WriteData((NJS_OBJECT**)0x02F1CBB4, &Tikal_Object);
	WriteData((NJS_OBJECT**)0x02F21B8C, &Tikal_Object);
	WriteData((NJS_OBJECT**)0x02F2D344, &Tikal_Object);
	WriteData((NJS_OBJECT**)0x02F33DFC, &Tikal_Object);
	WriteData((NJS_OBJECT**)0x02F3E204, &Tikal_Object);
	WriteData((NJS_OBJECT**)0x02FA7544, &Tikal_Object);
	WriteData((NJS_OBJECT**)0x02FAA58C, &Tikal_Object);
	WriteData((NJS_OBJECT**)0x02FAB794, &Tikal_Object);
	WriteData((NJS_OBJECT**)0x02FB1F1C, &Tikal_Object);
	WriteData((NJS_OBJECT**)0x02FBFAA4, &Tikal_Object);
	WriteData((NJS_OBJECT**)0x030DF19C, &Tikal_Object);
	WriteData((NJS_OBJECT**)0x030E6944, &Tikal_Object);
	WriteData((NJS_OBJECT**)0x030EE53C, &Tikal_Object);
	WriteData((NJS_OBJECT**)0x030F6004, &Tikal_Object);
	WriteData((NJS_OBJECT**)0x030F854C, &Tikal_Object);
	WriteData((NJS_OBJECT**)0x03100084, &Tikal_Object);
	WriteData((NJS_OBJECT**)0x03103DCC, &Tikal_Object);
	WriteData((WeldInfo**)0x007B41AB, TikalWeldInfo);

	//Eggman
	ResizeTextureList((NJS_TEXLIST*)0x00892A20, 19);
	WriteData((NJS_OBJECT**)0x0089E254, &Eggman_Object);
	WriteData((NJS_OBJECT**)0x008A094C, &Eggman_Object);
	WriteData((NJS_OBJECT**)0x008A3564, &Eggman_Object);
	WriteData((NJS_OBJECT**)0x008A513C, &Eggman_Object);
	WriteData((NJS_OBJECT**)0x008A6BF4, &Eggman_Object);
	WriteData((NJS_OBJECT**)0x008A8A9C, &Eggman_Object);
	WriteData((NJS_OBJECT**)0x008AC3F4, &Eggman_Object);
	WriteData((NJS_OBJECT**)0x008B1CCC, &Eggman_Object);
	WriteData((NJS_OBJECT**)0x0111B72C, &Eggman_Object);
	WriteData((NJS_OBJECT**)0x02D00DF4, &Eggman_Object);
	WriteData((NJS_OBJECT**)0x02D027EC, &Eggman_Object);
	WriteData((NJS_OBJECT**)0x02D06F6C, &Eggman_Object);
	WriteData((NJS_OBJECT**)0x02D08DF4, &Eggman_Object);
	WriteData((NJS_OBJECT**)0x02D0AC0C, &Eggman_Object);
	WriteData((NJS_OBJECT**)0x02F9470C, &Eggman_Object);
	WriteData((NJS_OBJECT**)0x0303D284, &Eggman_Object);
	WriteData((NJS_OBJECT**)0x0303EE9C, &Eggman_Object);
	WriteData((NJS_OBJECT**)0x03041A44, &Eggman_Object);
	WriteData((NJS_OBJECT**)0x0304E9AC, &Eggman_Object);
	WriteData((NJS_OBJECT**)0x030C62BC, &Eggman_Object);
	WriteData((NJS_OBJECT**)0x030C7E34, &Eggman_Object);
	WriteData((NJS_OBJECT**)0x03136234, &Eggman_Object);
	WriteData((NJS_OBJECT**)0x0313EB3C, &Eggman_Object);
	WriteData((NJS_OBJECT**)0x03141254, &Eggman_Object);
	WriteData((NJS_OBJECT**)0x03142C4C, &Eggman_Object);
	WriteData((WeldInfo**)0x007B4FBF, EggmanWeldList);

	//Sky Chase
	WriteData((NJS_OBJECT**)0x0028B7A0C, &Tornado1_Object);
	WriteData((NJS_OBJECT**)0x0028BA71C, &Tornado1_Object);
	WriteData((NJS_OBJECT**)0x0028BDDBC, &Tornado1_Object);
	WriteData((NJS_OBJECT**)0x0028C09FC, &Tornado1_Object);
	WriteData((NJS_OBJECT**)0x002935DFC, &TornadoDestroyed_Object);
	WriteData((NJS_OBJECT**)0x0027EFDDC, &Tornado2Before_Object);
	WriteData((NJS_OBJECT**)0x0027F2AA4, &Tornado2Before_Object);
	WriteData((NJS_OBJECT**)0x0027F612C, &Tornado2Before_Object);
	WriteData((NJS_OBJECT**)0x0027F8974, &Tornado2Before_Object);
	WriteData((NJS_OBJECT**)0x0028988FC, &Tornado2Transformation_Object);
	WriteData((NJS_OBJECT**)0x00280F23C, &Tornado2Change_Object);
	WriteData((NJS_OBJECT**)0x002811CE4, &Tornado2Change_Object);
	WriteData((NJS_OBJECT**)0x002814D9C, &Tornado2Change_Object);
	WriteData((NJS_OBJECT**)0x002817514, &Tornado2Change_Object);

	//Event Data
	WriteData((NJS_ACTION**)0x006BF039, &EV_TR1_Action);
	WriteData((NJS_ACTION**)0x006BF3AA, &EV_TR1_Action);
	WriteData((NJS_ACTION**)0x006BF6B7, &EV_TR1_Action);
	WriteData((NJS_ACTION**)0x006DF5F4, &EV_TR1_Action);
	WriteData((NJS_ACTION**)0x006DFE45, &EV_TR1_Action);
	WriteData((NJS_OBJECT***)0x006BEE81, &EV_TR1_Object.child);
	WriteData((NJS_OBJECT***)0x006BEEA1, &EV_TR1_Object.child);
	WriteData((NJS_OBJECT***)0x006BEEC1, &EV_TR1_Object.child);
	WriteData((NJS_OBJECT***)0x006BEF11, &EV_TR1_Object.child);
	WriteData((NJS_OBJECT***)0x006DF421, &EV_TR1_Object.child);
	WriteData((NJS_OBJECT***)0x006DF441, &EV_TR1_Object.child);
	WriteData((NJS_OBJECT***)0x007D7BE1, &EV_TR1_Object.child);
	WriteData((NJS_OBJECT***)0x007D7C11, &EV_TR1_Object.child);
	WriteData((NJS_OBJECT***)0x007D7D01, &EV_TR1_Object.child);
	WriteData((NJS_OBJECT**)0x00664C3E, &OBJECT_SonicPointingFinger);
	WriteData((NJS_OBJECT**)0x0069E24B, &OBJECT_SonicPointingFinger);
	WriteData((NJS_OBJECT**)0x006D010C, &OBJECT_SonicPointingFinger);
	WriteData((NJS_OBJECT**)0x006D711E, &OBJECT_SonicPointingFinger);
	WriteData((NJS_ACTION**)0x006B9527, &EV_TR2BEFORE_Action);
	WriteData((NJS_ACTION**)0x006BA8B6, &EV_TR2BEFORE_Action);
	WriteData((NJS_ACTION**)0x006BA9E1, &EV_TR2BEFORE_Action);
	WriteData((NJS_ACTION**)0x006BABEB, &EV_TR2BEFORE_Action);
	WriteData((NJS_ACTION**)0x006BACF8, &EV_TR2BEFORE_Action);
	WriteData((NJS_ACTION**)0x006DA505, &EV_TR2BEFORE_Action);
	WriteData((NJS_OBJECT***)0x006B9281, &EV_TR2BEFORE_Object.child);
	WriteData((NJS_OBJECT***)0x006B9291, &EV_TR2BEFORE_Object.child);
	WriteData((NJS_OBJECT***)0x006BA0A1, &EV_TR2BEFORE_Object.child);
	WriteData((NJS_OBJECT***)0x006BA0B1, &EV_TR2BEFORE_Object.child);
	WriteData((NJS_OBJECT***)0x006DA2B1, &EV_TR2BEFORE_Object.child);
	WriteData((NJS_OBJECT***)0x006DA2C1, &EV_TR2BEFORE_Object.child);
	WriteData((NJS_OBJECT***)0x007D7B41, &EV_TR2BEFORE_Object.child);
	WriteData((NJS_OBJECT***)0x007D7B71, &EV_TR2BEFORE_Object.child);
	WriteData((NJS_OBJECT***)0x007D7B91, &EV_TR2BEFORE_Object.child);
	WriteData((NJS_OBJECT***)0x007D7BC1, &EV_TR2BEFORE_Object.child);
	WriteData((NJS_OBJECT***)0x007D7CB1, &EV_TR2BEFORE_Object.child);
	WriteData((NJS_OBJECT***)0x007D7CE1, &EV_TR2BEFORE_Object.child);
	WriteData((NJS_ACTION**)0x006AF5FE, &EV_TR2CHANGE_Action);
	WriteData((NJS_ACTION**)0x006AF92D, &EV_TR2CHANGE_Action);
	WriteData((NJS_ACTION**)0x006CDE0E, &EV_TR2CHANGE_Action);
	WriteData((NJS_ACTION**)0x006CE10D, &EV_TR2CHANGE_Action);
	ResizeTextureList((NJS_TEXLIST *)0x033315E4, 33);
	WriteData((NJS_OBJECT**)0x03342074, &EV_TailsProtoPlane);
	WriteData((NJS_OBJECT**)0x03344EAC, &EV_TailsProtoPlane);
	WriteData((NJS_OBJECT**)0x03347734, &EV_TailsProtoPlane);
	WriteData((NJS_OBJECT**)0x0334A8FC, &EV_TailsProtoPlane);
	WriteData((NJS_OBJECT**)0x006F9483, &EV_TailsCineHead_DC);
	WriteData((NJS_OBJECT**)0x0334A910, &EV_TailsCineHead_DC);
	WriteData((NJS_OBJECT**)0x0334A924, &EV_TailsCineHead_DC);
	WriteData((NJS_OBJECT**)0x0334A938, &EV_TailsCineHead_DC);
	WriteData((NJS_MOTION**)0x03375D88, &EV_Tails02);
	WriteData((NJS_MOTION**)0x03375D98, &EV_Tails01);
	WriteData((NJS_MOTION**)0x03375DA8, &EV_Tails01);
	WriteData((NJS_MOTION**)0x03375DB8, &EV_Tails00);

	//Functions
	WriteJump((void*)0x00493500, Sonic_MorphStretchyFeet_asm);
	WriteJump((void*)0x007D0B50, InitSonicWeldInfo_mod);
	WriteJump((void*)0x007D14D0, InitNPCSonicWeldInfo_mod);
	WriteJump((void*)0x0045B840, Tails_Jiggle_Main);
	WriteJump((void*)0x007C6D80, InitTailsWeldInfo_mod);
	WriteJump((void*)0x007C7560, InitNPCTailsWeldInfo_mod);
	WriteJump((void*)0x007C94D0, InitKnucklesWeldInfo_mod);
	WriteJump((void*)0x007C9C80, InitNPCKnucklesWeldInfo_mod);
	WriteJump((void*)0x004726A0, Knuckles_Upgrades_mod);
	WriteJump((void*)0x007CCB90, InitAmyWeldInfo_mod);
	WriteJump((void*)0x007CD000, InitNPCAmyWeldInfo_mod);
	WriteJump((void*)0x007CE860, InitBigWeldInfo_mod);
}

extern "C" __declspec(dllexport) const ModInfo SADXModInfo = { ModLoaderVer };