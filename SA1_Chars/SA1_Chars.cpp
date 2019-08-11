#include "stdafx.h"

#include <SADXModLoader.h>
#include <IniFile.hpp>
#include <cmath>

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
#include "lanternapi.h"
#include "MetalSonic.h"

#define ReplacePVM(a, b) helperFunctions.ReplaceFile("system\\" a ".PVM", "system\\" b ".PVM");
NJS_MATERIAL *TemporaryMaterialArray[] = { nullptr };

//Customization Options
enum MSHoverBehavior { Normal, Swap, Always };
enum StretchyShoesBehavior { Regular, LSShoeMorphs, Disable };

static bool EnableSonic = true;
static bool EnableMiles = true;
static bool EnableKnuckles = true;
static bool EnableAmy = true;
static bool EnableBig = true;
static bool EnableGamma = true;
static bool EnableTikal = true;
static bool EnableEggman = true;
static bool EnableSkychase = true;
static bool DisableSaturnSkyChase = false;
static int StretchyShoes = Regular;
static int MSHover = Normal;
static bool EnableCDMetalSonic = true;
static bool EnableExtras = false;

//Additional Data Bits
DataPointer(int, EVENT_ID, 0x03B2C570);
FunctionPointer(void, PlaySonicIdleVoice, (int a1), 0x442360);
static bool BigRodIgnoresSpecular = false;

//Replacement Functions

void PlaySonicIdleVoice_r(int a1)
{
	if (MetalSonicFlag)
	{
		PlayVoice(2044 + rand() % 5);
	}
	else PlaySonicIdleVoice(a1);
}

void __cdecl Sonic_MorphStretchyFeet_c(CharObj2* a1)
{
	float a4; // ST10_4@3
	float v2; // ST10_4@5
	NJS_MODEL_SADX *v3; // ecx@5
	float v4; // ST10_4@10
	float v5; // ST10_4@13

	if (SONIC_OBJECTS[19]->sibling == SONIC_OBJECTS[58])
	{
		if (a1->AnimationThing.Index == 13)
		{
			if (a1->AnimationThing.Frame >= 16.0f)
			{
				if (a1->AnimationThing.Frame <= 24.0f)
				{
					a1->SomeFrameNumberThing = 0.0f;
					v3 = &LS_Morph_L03;
				}
				else
				{
					v2 = (a1->AnimationThing.Frame - 24.0f) * 0.125f;
					a1->SomeFrameNumberThing = v2;
					MorphPoints(&LS_Morph_L03, &LS_Morph_L02, &LS_Morph_L01, v2);
					v3 = &LS_Morph_L01;
				}
				SONIC_OBJECTS[59]->model = v3;
			}
			else
			{
				a4 = (16.0f - a1->AnimationThing.Frame) * 0.0625f;
				a1->SomeFrameNumberThing = a4;
				MorphPoints(&LS_Morph_L03, &LS_Morph_L02, &LS_Morph_L01, a4);
				SONIC_OBJECTS[59]->model = &LS_Morph_L01;
			}
			if (a1->AnimationThing.Frame < 8.0f || a1->AnimationThing.Frame > 16.0f)
			{
				if (a1->AnimationThing.Frame <= 16.0f || a1->AnimationThing.Frame > 32.0f)
				{
					a1->TailsFlightTime = 0.0f;
					SONIC_OBJECTS[61]->model = &LS_Morph_R03;
				}
				else
				{
					v5 = (32.0f - a1->AnimationThing.Frame) * 0.0625f;
					a1->TailsFlightTime = v5;
					MorphPoints(&LS_Morph_R03, &LS_Morph_R02, &LS_Morph_R01, v5);
					SONIC_OBJECTS[61]->model = &LS_Morph_R01;
				}
			}
			else
			{
				v4 = (a1->AnimationThing.Frame - 8.0f) * 0.125f;
				a1->TailsFlightTime = v4;
				MorphPoints(&LS_Morph_R03, &LS_Morph_R02, &LS_Morph_R01, v4);
				SONIC_OBJECTS[61]->model = &LS_Morph_R01;
			}
		}
		else
		{
			a1->SomeFrameNumberThing = 0.0f;
			a1->TailsFlightTime = 0.0f;
			SONIC_OBJECTS[59]->model = &attach_00581880;
			SONIC_OBJECTS[61]->model = &attach_00582578;
		}
	}
	else
	{
		if (a1->AnimationThing.Index == 13)
		{
			if (a1->AnimationThing.Frame >= 16.0f)
			{
				if (a1->AnimationThing.Frame <= 24.0f)
				{
					a1->SomeFrameNumberThing = 0.0f;
					v3 = SONIC_MODELS[4];
				}
				else
				{
					v2 = (a1->AnimationThing.Frame - 24.0f) * 0.125f;
					a1->SomeFrameNumberThing = v2;
					MorphPoints(SONIC_MODELS[4], SONIC_MODELS[3], SONIC_MODELS[2], v2);
					v3 = SONIC_MODELS[2];
				}
				SONIC_OBJECTS[21]->model = v3;
			}
			else
			{
				a4 = (16.0f - a1->AnimationThing.Frame) * 0.0625f;
				a1->SomeFrameNumberThing = a4;
				MorphPoints(SONIC_MODELS[4], SONIC_MODELS[3], SONIC_MODELS[2], a4);
				SONIC_OBJECTS[21]->model = SONIC_MODELS[2];
			}
			if (a1->AnimationThing.Frame < 8.0f || a1->AnimationThing.Frame > 16.0f)
			{
				if (a1->AnimationThing.Frame <= 16.0f || a1->AnimationThing.Frame > 32.0f)
				{
					a1->TailsFlightTime = 0.0f;
					SONIC_OBJECTS[16]->model = SONIC_MODELS[7];
				}
				else
				{
					v5 = (32.0f - a1->AnimationThing.Frame) * 0.0625f;
					a1->TailsFlightTime = v5;
					MorphPoints(SONIC_MODELS[7], SONIC_MODELS[6], SONIC_MODELS[5], v5);
					SONIC_OBJECTS[16]->model = SONIC_MODELS[5];
				}
			}
			else
			{
				v4 = (a1->AnimationThing.Frame - 8.0f) * 0.125f;
				a1->TailsFlightTime = v4;
				MorphPoints(SONIC_MODELS[7], SONIC_MODELS[6], SONIC_MODELS[5], v4);
				SONIC_OBJECTS[16]->model = SONIC_MODELS[5];
			}
		}
		else
		{
			a1->SomeFrameNumberThing = 0.0f;
			a1->TailsFlightTime = 0.0f;
			SONIC_OBJECTS[21]->model = SONIC_MODELS[0];
			SONIC_OBJECTS[16]->model = SONIC_MODELS[1];
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

static void __cdecl Tails_Jiggle_mod(ObjectMaster *_this)
{
	NJS_POINT3 *_src_points; // esi@4
	float v21; // st7@32
	Sint32 nbPoint; // [sp+14h] [bp-14h]@4
	NJS_VECTOR a2; // [sp+1Ch] [bp-Ch]@29

	EntityData2* v1 = (EntityData2*)_this->Data2;
	EntityData1* v2 = _this->Data1;
	int v3 = v2->CharIndex;

	if (!EntityData1Ptrs[v3])
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
	SonicWeldInfo[0].VertexPairCount = (uint8_t)(LengthOfArray(Sonic_UpperArmIndices_DC) / 2);
	SonicWeldInfo[0].WeldType = 2;
	SonicWeldInfo[0].VertIndexes = Sonic_UpperArmIndices_DC;
	SonicWeldInfo[1].BaseModel = SONIC_OBJECTS[0];
	SonicWeldInfo[1].ModelA = SONIC_OBJECTS[2];
	SonicWeldInfo[1].ModelB = SONIC_OBJECTS[3];
	SonicWeldInfo[1].VertexPairCount = (uint8_t)(LengthOfArray(Sonic_LowerArmIndices_DC) / 2);
	SonicWeldInfo[1].WeldType = 2;
	SonicWeldInfo[1].anonymous_5 = 0;
	SonicWeldInfo[1].VertexBuffer = 0;
	SonicWeldInfo[1].VertIndexes = Sonic_LowerArmIndices_DC;
	SonicWeldInfo[2].BaseModel = SONIC_OBJECTS[0];
	SonicWeldInfo[2].ModelA = SONIC_OBJECTS[7];
	SonicWeldInfo[2].ModelB = SONIC_OBJECTS[8];
	SonicWeldInfo[2].VertexPairCount = (uint8_t)(LengthOfArray(Sonic_UpperArmIndices_DC) / 2);
	SonicWeldInfo[2].WeldType = 2;
	SonicWeldInfo[2].anonymous_5 = 0;
	SonicWeldInfo[2].VertexBuffer = 0;
	SonicWeldInfo[2].VertIndexes = Sonic_UpperArmIndices_DC;
	SonicWeldInfo[3].BaseModel = SONIC_OBJECTS[0];
	SonicWeldInfo[3].ModelA = SONIC_OBJECTS[8];
	v0 = SONIC_OBJECTS[9];
	SonicWeldInfo[3].VertIndexes = Sonic_LowerArmIndices_DC;
	SonicWeldInfo[3].ModelB = v0;
	SonicWeldInfo[3].VertexPairCount = (uint8_t)(LengthOfArray(Sonic_LowerArmIndices_DC) / 2);
	SonicWeldInfo[3].WeldType = 2;
	SonicWeldInfo[3].anonymous_5 = 0;
	SonicWeldInfo[3].VertexBuffer = 0;
	SonicWeldInfo[4].BaseModel = SONIC_OBJECTS[0];
	SonicWeldInfo[4].ModelA = SONIC_OBJECTS[12];
	SonicWeldInfo[4].ModelB = SONIC_OBJECTS[13];
	SonicWeldInfo[4].VertexPairCount = (uint8_t)(LengthOfArray(Sonic_UpperLegIndices_DC) / 2);
	SonicWeldInfo[4].WeldType = 2;
	SonicWeldInfo[4].anonymous_5 = 0;
	SonicWeldInfo[4].VertexBuffer = 0;
	SonicWeldInfo[4].VertIndexes = Sonic_UpperLegIndices_DC;
	SonicWeldInfo[5].BaseModel = SONIC_OBJECTS[0];
	SonicWeldInfo[5].ModelA = SONIC_OBJECTS[13];
	SonicWeldInfo[5].ModelB = SONIC_OBJECTS[14];
	SonicWeldInfo[5].VertexPairCount = (uint8_t)(LengthOfArray(Sonic_LowerLegIndices_DC) / 2);
	SonicWeldInfo[5].WeldType = 2;
	SonicWeldInfo[5].anonymous_5 = 0;
	SonicWeldInfo[5].VertexBuffer = 0;
	SonicWeldInfo[5].VertIndexes = Sonic_LowerLegIndices_DC;
	SonicWeldInfo[6].BaseModel = SONIC_OBJECTS[0];
	SonicWeldInfo[6].ModelA = SONIC_OBJECTS[17];
	v1 = SONIC_OBJECTS[18];
	SonicWeldInfo[6].VertIndexes = Sonic_UpperLegIndices_DC;
	SonicWeldInfo[6].ModelB = v1;
	SonicWeldInfo[6].VertexPairCount = (uint8_t)(LengthOfArray(Sonic_UpperLegIndices_DC) / 2);
	SonicWeldInfo[6].WeldType = 2;
	SonicWeldInfo[6].anonymous_5 = 0;
	SonicWeldInfo[6].VertexBuffer = 0;
	SonicWeldInfo[7].BaseModel = SONIC_OBJECTS[0];
	SonicWeldInfo[7].ModelA = SONIC_OBJECTS[18];
	SonicWeldInfo[7].ModelB = SONIC_OBJECTS[19];
	SonicWeldInfo[7].VertexPairCount = (uint8_t)(LengthOfArray(Sonic_LowerLegIndices_DC) / 2);
	SonicWeldInfo[7].WeldType = 2;
	SonicWeldInfo[7].anonymous_5 = 0;
	SonicWeldInfo[7].VertexBuffer = 0;
	SonicWeldInfo[7].VertIndexes = Sonic_LowerLegIndices_DC;
	SonicWeldInfo[8].BaseModel = SONIC_OBJECTS[0];
	SonicWeldInfo[8].ModelA = SONIC_OBJECTS[15];
	SonicWeldInfo[8].ModelB = SONIC_OBJECTS[16];
	SonicWeldInfo[8].VertexPairCount = (uint8_t)(LengthOfArray(Sonic_ShoeIndices_DC) / 2);
	SonicWeldInfo[8].WeldType = 2;
	SonicWeldInfo[8].anonymous_5 = 0;
	SonicWeldInfo[8].VertexBuffer = 0;
	SonicWeldInfo[8].VertIndexes = Sonic_ShoeIndices_DC;
	SonicWeldInfo[9].BaseModel = SONIC_OBJECTS[0];
	SonicWeldInfo[9].ModelA = SONIC_OBJECTS[20];
	v2 = SONIC_OBJECTS[21];
	SonicWeldInfo[9].VertIndexes = Sonic_ShoeIndices_DC;
	SonicWeldInfo[9].ModelB = v2;
	SonicWeldInfo[9].VertexPairCount = (uint8_t)(LengthOfArray(Sonic_ShoeIndices_DC) / 2);
	SonicWeldInfo[9].WeldType = 2;
	SonicWeldInfo[9].anonymous_5 = 0;
	SonicWeldInfo[9].VertexBuffer = 0;
	SonicWeldInfo[10].BaseModel = SONIC_OBJECTS[0];
	SonicWeldInfo[10].ModelA = SONIC_OBJECTS[10];
	SonicWeldInfo[10].ModelB = SONIC_OBJECTS[11];
	SonicWeldInfo[10].VertexPairCount = (uint8_t)(LengthOfArray(Sonic_HandIndices_DC) / 2);
	SonicWeldInfo[10].WeldType = 2;
	SonicWeldInfo[10].anonymous_5 = 0;
	SonicWeldInfo[10].VertexBuffer = 0;
	SonicWeldInfo[10].VertIndexes = Sonic_HandIndices_DC;
	SonicWeldInfo[11].BaseModel = SONIC_OBJECTS[0];
	SonicWeldInfo[11].ModelA = SONIC_OBJECTS[4];
	SonicWeldInfo[11].ModelB = SONIC_OBJECTS[5];
	SonicWeldInfo[11].VertexPairCount = (uint8_t)(LengthOfArray(Sonic_HandIndices_DC) / 2);
	SonicWeldInfo[11].WeldType = 2;
	SonicWeldInfo[11].anonymous_5 = 0;
	SonicWeldInfo[11].VertexBuffer = 0;
	SonicWeldInfo[11].VertIndexes = Sonic_HandIndices_DC;
	SonicWeldInfo[12].BaseModel = SONIC_OBJECTS[0];
	SonicWeldInfo[12].ModelA = SONIC_OBJECTS[58];
	SonicWeldInfo[12].ModelB = SONIC_OBJECTS[59];
	SonicWeldInfo[12].VertexPairCount = (uint8_t)(LengthOfArray(Sonic_ShoeIndices_DC) / 2);
	SonicWeldInfo[12].WeldType = 2;
	SonicWeldInfo[12].anonymous_5 = 0;
	SonicWeldInfo[12].VertexBuffer = 0;
	SonicWeldInfo[12].VertIndexes = Sonic_ShoeIndices_DC;
	SonicWeldInfo[13].BaseModel = SONIC_OBJECTS[0];
	SonicWeldInfo[13].ModelA = SONIC_OBJECTS[60];
	SonicWeldInfo[13].ModelB = SONIC_OBJECTS[61];
	SonicWeldInfo[13].VertexPairCount = (uint8_t)(LengthOfArray(Sonic_ShoeIndices_DC) / 2);
	SonicWeldInfo[13].WeldType = 2;
	SonicWeldInfo[13].anonymous_5 = 0;
	SonicWeldInfo[13].VertexBuffer = 0;
	SonicWeldInfo[13].VertIndexes = Sonic_ShoeIndices_DC;
	SonicWeldInfo[14].BaseModel = SONIC_OBJECTS[0];
	SonicWeldInfo[14].ModelA = SONIC_OBJECTS[2];
	SonicWeldInfo[14].ModelB = SONIC_OBJECTS[63];
	SonicWeldInfo[14].VertexPairCount = (uint8_t)(LengthOfArray(Sonic_LowerArmIndices_DC) / 2);
	SonicWeldInfo[14].WeldType = 2;
	SonicWeldInfo[14].anonymous_5 = 0;
	SonicWeldInfo[14].VertexBuffer = 0;
	SonicWeldInfo[14].VertIndexes = Sonic_LowerArmIndices_DC;
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
	SonicWeldInfo[22].VertexPairCount = (uint8_t)(LengthOfArray(Sonic_UpperArmIndices_DC) / 2);
	SonicWeldInfo[22].WeldType = 2;
	SonicWeldInfo[22].anonymous_5 = 0;
	SonicWeldInfo[22].VertexBuffer = 0;
	SonicWeldInfo[22].VertIndexes = Sonic_UpperArmIndices_DC;
	SonicWeldInfo[23].BaseModel = SONIC_OBJECTS[22];
	SonicWeldInfo[23].ModelA = SONIC_OBJECTS[24];
	SonicWeldInfo[23].ModelB = SONIC_OBJECTS[25];
	SonicWeldInfo[23].VertexPairCount = (uint8_t)(LengthOfArray(Sonic_LowerArmIndices_DC) / 2);
	SonicWeldInfo[23].WeldType = 2;
	SonicWeldInfo[23].anonymous_5 = 0;
	SonicWeldInfo[23].VertexBuffer = 0;
	SonicWeldInfo[23].VertIndexes = Sonic_LowerArmIndices_DC;
	SonicWeldInfo[24].BaseModel = SONIC_OBJECTS[22];
	SonicWeldInfo[24].ModelA = SONIC_OBJECTS[28];
	SonicWeldInfo[24].ModelB = SONIC_OBJECTS[29];
	SonicWeldInfo[24].VertexPairCount = (uint8_t)(LengthOfArray(Sonic_UpperArmIndices_DC) / 2);
	SonicWeldInfo[24].WeldType = 2;
	SonicWeldInfo[24].anonymous_5 = 0;
	SonicWeldInfo[24].VertexBuffer = 0;
	SonicWeldInfo[24].VertIndexes = Sonic_UpperArmIndices_DC;
	SonicWeldInfo[25].BaseModel = SONIC_OBJECTS[22];
	SonicWeldInfo[25].ModelA = SONIC_OBJECTS[29];
	SonicWeldInfo[25].ModelB = SONIC_OBJECTS[30];
	SonicWeldInfo[25].VertexPairCount = (uint8_t)(LengthOfArray(Sonic_LowerArmIndices_DC) / 2);
	SonicWeldInfo[25].WeldType = 2;
	SonicWeldInfo[25].anonymous_5 = 0;
	SonicWeldInfo[25].VertexBuffer = 0;
	SonicWeldInfo[25].VertIndexes = Sonic_LowerArmIndices_DC;
	SonicWeldInfo[26].BaseModel = SONIC_OBJECTS[22];
	SonicWeldInfo[26].ModelA = SONIC_OBJECTS[33];
	SonicWeldInfo[26].ModelB = SONIC_OBJECTS[34];
	SonicWeldInfo[26].VertexPairCount = (uint8_t)(LengthOfArray(Sonic_UpperLegIndices_DC) / 2);
	SonicWeldInfo[26].WeldType = 2;
	SonicWeldInfo[26].anonymous_5 = 0;
	SonicWeldInfo[26].VertexBuffer = 0;
	SonicWeldInfo[26].VertIndexes = Sonic_UpperLegIndices_DC;
	SonicWeldInfo[27].BaseModel = SONIC_OBJECTS[22];
	SonicWeldInfo[27].ModelA = SONIC_OBJECTS[34];
	SonicWeldInfo[27].ModelB = SONIC_OBJECTS[35];
	SonicWeldInfo[27].VertexPairCount = (uint8_t)(LengthOfArray(Sonic_LowerLegIndices_DC) / 2);
	SonicWeldInfo[27].WeldType = 2;
	SonicWeldInfo[27].anonymous_5 = 0;
	SonicWeldInfo[27].VertexBuffer = 0;
	SonicWeldInfo[27].VertIndexes = Sonic_LowerLegIndices_DC;
	SonicWeldInfo[28].BaseModel = SONIC_OBJECTS[22];
	SonicWeldInfo[28].ModelA = SONIC_OBJECTS[38];
	v3 = SONIC_OBJECTS[39];
	SonicWeldInfo[28].VertIndexes = Sonic_UpperLegIndices_DC;
	SonicWeldInfo[28].ModelB = v3;
	SonicWeldInfo[28].VertexPairCount = (uint8_t)(LengthOfArray(Sonic_UpperLegIndices_DC) / 2);
	SonicWeldInfo[28].WeldType = 2;
	SonicWeldInfo[28].anonymous_5 = 0;
	SonicWeldInfo[28].VertexBuffer = 0;
	SonicWeldInfo[29].BaseModel = SONIC_OBJECTS[22];
	SonicWeldInfo[29].ModelA = SONIC_OBJECTS[39];
	SonicWeldInfo[29].ModelB = SONIC_OBJECTS[40];
	SonicWeldInfo[29].VertexPairCount = (uint8_t)(LengthOfArray(Sonic_LowerLegIndices_DC) / 2);
	SonicWeldInfo[29].WeldType = 2;
	SonicWeldInfo[29].anonymous_5 = 0;
	SonicWeldInfo[29].VertexBuffer = 0;
	SonicWeldInfo[29].VertIndexes = Sonic_LowerLegIndices_DC;
	SonicWeldInfo[30].BaseModel = SONIC_OBJECTS[22];
	SonicWeldInfo[30].ModelA = SONIC_OBJECTS[36];
	SonicWeldInfo[30].ModelB = SONIC_OBJECTS[37];
	SonicWeldInfo[30].VertexPairCount = (uint8_t)(LengthOfArray(Sonic_ShoeIndices_DC) / 2);
	SonicWeldInfo[30].WeldType = 2;
	SonicWeldInfo[30].anonymous_5 = 0;
	SonicWeldInfo[30].VertexBuffer = 0;
	SonicWeldInfo[30].VertIndexes = Sonic_ShoeIndices_DC;
	SonicWeldInfo[31].BaseModel = SONIC_OBJECTS[22];
	SonicWeldInfo[31].ModelA = SONIC_OBJECTS[41];
	SonicWeldInfo[31].ModelB = SONIC_OBJECTS[42];
	SonicWeldInfo[31].VertexPairCount = (uint8_t)(LengthOfArray(Sonic_ShoeIndices_DC) / 2);
	SonicWeldInfo[31].WeldType = 2;
	SonicWeldInfo[31].anonymous_5 = 0;
	SonicWeldInfo[31].VertexBuffer = 0;
	SonicWeldInfo[31].VertIndexes = Sonic_ShoeIndices_DC;
	SonicWeldInfo[32].BaseModel = SONIC_OBJECTS[22];
	SonicWeldInfo[32].ModelA = SONIC_OBJECTS[31];
	SonicWeldInfo[32].ModelB = SONIC_OBJECTS[32];
	SonicWeldInfo[32].VertexPairCount = (uint8_t)(LengthOfArray(Sonic_HandIndices_DC) / 2);
	SonicWeldInfo[32].WeldType = 2;
	SonicWeldInfo[32].anonymous_5 = 0;
	SonicWeldInfo[32].VertexBuffer = 0;
	SonicWeldInfo[32].VertIndexes = Sonic_HandIndices_DC;
	SonicWeldInfo[33].BaseModel = SONIC_OBJECTS[22];
	SonicWeldInfo[33].ModelA = SONIC_OBJECTS[26];
	v4 = SONIC_OBJECTS[27];
	SonicWeldInfo[33].anonymous_5 = 0;
	SonicWeldInfo[33].VertexBuffer = 0;
	SonicWeldInfo[33].VertIndexes = Sonic_HandIndices_DC;
	SonicWeldInfo[33].ModelB = v4;
	SonicWeldInfo[33].VertexPairCount = (uint8_t)(LengthOfArray(Sonic_HandIndices_DC) / 2);
	SonicWeldInfo[33].WeldType = 2;
	SonicWeldInfo[34].BaseModel = SONIC_OBJECTS[22];
	SonicWeldInfo[34].ModelA = SONIC_OBJECTS[31];
	SonicWeldInfo[34].ModelB = SONIC_OBJECTS[32];
	SonicWeldInfo[34].anonymous_5 = 0;
	SonicWeldInfo[34].VertexBuffer = 0;
	SonicWeldInfo[34].VertexPairCount = 4;
	SonicWeldInfo[34].VertIndexes = Sonic_HandIndices_DC;
	SonicWeldInfo[34].WeldType = 2;
	SonicWeldInfo[35].BaseModel = SONIC_OBJECTS[22];
	SonicWeldInfo[35].ModelA = SONIC_OBJECTS[26];
	v5 = SONIC_OBJECTS[27];
	SonicWeldInfo[35].anonymous_5 = 0;
	SonicWeldInfo[35].VertexBuffer = 0;
	SonicWeldInfo[36].BaseModel = 0;
	SonicWeldInfo[36].ModelA = 0;
	SonicWeldInfo[36].ModelB = 0;
	SonicWeldInfo[35].VertIndexes = Sonic_HandIndices_DC;
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
	NPCSonicWeldInfo[0].VertIndexes = Sonic_UpperArmIndices_DC;
	NPCSonicWeldInfo[0].WeldType = 2;
	NPCSonicWeldInfo[0].VertexPairCount = (uint8_t)(LengthOfArray(Sonic_UpperArmIndices_DC) / 2);
	NPCSonicWeldInfo[1].BaseModel = *SONIC_OBJECTS;
	NPCSonicWeldInfo[1].ModelA = SONIC_OBJECTS[2];
	NPCSonicWeldInfo[1].ModelB = SONIC_OBJECTS[3];
	NPCSonicWeldInfo[1].VertexPairCount = (uint8_t)(LengthOfArray(Sonic_LowerArmIndices_DC) / 2);
	NPCSonicWeldInfo[1].WeldType = 2;
	NPCSonicWeldInfo[1].anonymous_5 = 0;
	NPCSonicWeldInfo[1].VertexBuffer = 0;
	NPCSonicWeldInfo[1].VertIndexes = Sonic_LowerArmIndices_DC;
	NPCSonicWeldInfo[2].BaseModel = *SONIC_OBJECTS;
	NPCSonicWeldInfo[2].ModelA = SONIC_OBJECTS[7];
	NPCSonicWeldInfo[2].ModelB = SONIC_OBJECTS[8];
	NPCSonicWeldInfo[2].VertexPairCount = (uint8_t)(LengthOfArray(Sonic_UpperArmIndices_DC) / 2);
	NPCSonicWeldInfo[2].WeldType = 2;
	NPCSonicWeldInfo[2].anonymous_5 = 0;
	NPCSonicWeldInfo[2].VertexBuffer = 0;
	NPCSonicWeldInfo[2].VertIndexes = Sonic_UpperArmIndices_DC;
	NPCSonicWeldInfo[3].BaseModel = *SONIC_OBJECTS;
	NPCSonicWeldInfo[3].ModelA = SONIC_OBJECTS[8];
	v0 = SONIC_OBJECTS[9];
	NPCSonicWeldInfo[3].VertIndexes = Sonic_LowerArmIndices_DC;
	NPCSonicWeldInfo[3].ModelB = v0;
	NPCSonicWeldInfo[3].VertexPairCount = (uint8_t)(LengthOfArray(Sonic_LowerArmIndices_DC) / 2);
	NPCSonicWeldInfo[3].WeldType = 2;
	NPCSonicWeldInfo[3].anonymous_5 = 0;
	NPCSonicWeldInfo[3].VertexBuffer = 0;
	NPCSonicWeldInfo[4].BaseModel = *SONIC_OBJECTS;
	NPCSonicWeldInfo[4].ModelA = SONIC_OBJECTS[12];
	NPCSonicWeldInfo[4].ModelB = SONIC_OBJECTS[13];
	NPCSonicWeldInfo[4].VertexPairCount = (uint8_t)(LengthOfArray(Sonic_UpperLegIndices_DC) / 2);
	NPCSonicWeldInfo[4].WeldType = 2;
	NPCSonicWeldInfo[4].anonymous_5 = 0;
	NPCSonicWeldInfo[4].VertexBuffer = 0;
	NPCSonicWeldInfo[4].VertIndexes = Sonic_UpperLegIndices_DC;
	NPCSonicWeldInfo[5].BaseModel = *SONIC_OBJECTS;
	NPCSonicWeldInfo[5].ModelA = SONIC_OBJECTS[13];
	NPCSonicWeldInfo[5].ModelB = SONIC_OBJECTS[14];
	NPCSonicWeldInfo[5].VertexPairCount = (uint8_t)(LengthOfArray(Sonic_LowerLegIndices_DC) / 2);
	NPCSonicWeldInfo[5].WeldType = 2;
	NPCSonicWeldInfo[5].anonymous_5 = 0;
	NPCSonicWeldInfo[5].VertexBuffer = 0;
	NPCSonicWeldInfo[5].VertIndexes = Sonic_LowerLegIndices_DC;
	NPCSonicWeldInfo[6].BaseModel = *SONIC_OBJECTS;
	NPCSonicWeldInfo[6].ModelA = SONIC_OBJECTS[17];
	NPCSonicWeldInfo[6].ModelB = SONIC_OBJECTS[18];
	NPCSonicWeldInfo[6].VertexPairCount = (uint8_t)(LengthOfArray(Sonic_UpperLegIndices_DC) / 2);
	NPCSonicWeldInfo[6].WeldType = 2;
	NPCSonicWeldInfo[6].anonymous_5 = 0;
	NPCSonicWeldInfo[6].VertexBuffer = 0;
	NPCSonicWeldInfo[6].VertIndexes = Sonic_UpperLegIndices_DC;
	NPCSonicWeldInfo[7].BaseModel = *SONIC_OBJECTS;
	NPCSonicWeldInfo[7].ModelA = SONIC_OBJECTS[18];
	v1 = SONIC_OBJECTS[19];
	NPCSonicWeldInfo[7].VertIndexes = Sonic_LowerLegIndices_DC;
	NPCSonicWeldInfo[7].ModelB = v1;
	NPCSonicWeldInfo[7].VertexPairCount = (uint8_t)(LengthOfArray(Sonic_LowerLegIndices_DC) / 2);
	NPCSonicWeldInfo[7].WeldType = 2;
	NPCSonicWeldInfo[7].anonymous_5 = 0;
	NPCSonicWeldInfo[7].VertexBuffer = 0;
	NPCSonicWeldInfo[8].BaseModel = *SONIC_OBJECTS;
	NPCSonicWeldInfo[8].ModelA = SONIC_OBJECTS[15];
	NPCSonicWeldInfo[8].ModelB = SONIC_OBJECTS[16];
	NPCSonicWeldInfo[8].VertexPairCount = (uint8_t)(LengthOfArray(Sonic_ShoeIndices_DC) / 2);
	NPCSonicWeldInfo[8].WeldType = 2;
	NPCSonicWeldInfo[8].anonymous_5 = 0;
	NPCSonicWeldInfo[8].VertexBuffer = 0;
	NPCSonicWeldInfo[8].VertIndexes = Sonic_ShoeIndices_DC;
	NPCSonicWeldInfo[9].BaseModel = *SONIC_OBJECTS;
	NPCSonicWeldInfo[9].ModelA = SONIC_OBJECTS[20];
	v2 = SONIC_OBJECTS[21];
	NPCSonicWeldInfo[9].VertIndexes = Sonic_ShoeIndices_DC;
	NPCSonicWeldInfo[9].ModelB = v2;
	NPCSonicWeldInfo[9].VertexPairCount = (uint8_t)(LengthOfArray(Sonic_ShoeIndices_DC) / 2);
	NPCSonicWeldInfo[9].WeldType = 2;
	NPCSonicWeldInfo[9].anonymous_5 = 0;
	NPCSonicWeldInfo[9].VertexBuffer = 0;
	NPCSonicWeldInfo[10].BaseModel = *SONIC_OBJECTS;
	NPCSonicWeldInfo[10].ModelA = SONIC_OBJECTS[10];
	NPCSonicWeldInfo[10].ModelB = SONIC_OBJECTS[11];
	NPCSonicWeldInfo[10].VertexPairCount = (uint8_t)(LengthOfArray(Sonic_HandIndices_DC) / 2);
	NPCSonicWeldInfo[10].WeldType = 2;
	NPCSonicWeldInfo[10].anonymous_5 = 0;
	NPCSonicWeldInfo[10].VertexBuffer = 0;
	NPCSonicWeldInfo[10].VertIndexes = Sonic_HandIndices_DC;
	NPCSonicWeldInfo[11].BaseModel = *SONIC_OBJECTS;
	NPCSonicWeldInfo[11].ModelA = SONIC_OBJECTS[4];
	NPCSonicWeldInfo[11].ModelB = SONIC_OBJECTS[5];
	NPCSonicWeldInfo[11].VertexPairCount = (uint8_t)(LengthOfArray(Sonic_HandIndices_DC) / 2);
	NPCSonicWeldInfo[11].WeldType = 2;
	NPCSonicWeldInfo[11].anonymous_5 = 0;
	NPCSonicWeldInfo[11].VertexBuffer = 0;
	NPCSonicWeldInfo[11].VertIndexes = Sonic_HandIndices_DC;
	NPCSonicWeldInfo[12].BaseModel = *SONIC_OBJECTS;
	NPCSonicWeldInfo[12].ModelA = SONIC_OBJECTS[58];
	NPCSonicWeldInfo[12].ModelB = SONIC_OBJECTS[59];
	NPCSonicWeldInfo[12].VertexPairCount = (uint8_t)(LengthOfArray(Sonic_ShoeIndices_DC) / 2);
	NPCSonicWeldInfo[12].anonymous_5 = 0;
	NPCSonicWeldInfo[12].VertexBuffer = 0;
	NPCSonicWeldInfo[12].WeldType = 2;
	NPCSonicWeldInfo[12].VertIndexes = Sonic_ShoeIndices_DC;
	NPCSonicWeldInfo[13].BaseModel = *SONIC_OBJECTS;
	NPCSonicWeldInfo[13].ModelA = SONIC_OBJECTS[60];
	v3 = SONIC_OBJECTS[61];
	NPCSonicWeldInfo[13].anonymous_5 = 0;
	NPCSonicWeldInfo[13].VertexBuffer = 0;
	NPCSonicWeldInfo[13].ModelB = v3;
	NPCSonicWeldInfo[13].VertIndexes = Sonic_ShoeIndices_DC;
	NPCSonicWeldInfo[13].VertexPairCount = (uint8_t)(LengthOfArray(Sonic_ShoeIndices_DC) / 2);
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
	NPCSonicWeldInfo[14].VertexPairCount = (uint8_t)(LengthOfArray(Sonic_UpperArmIndices_DC) / 2);
	NPCSonicWeldInfo[14].ModelB = v4;
	NPCSonicWeldInfo[14].WeldType = 2;
	NPCSonicWeldInfo[14].VertIndexes = Sonic_UpperArmIndices_DC;
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
	TailsWeldInfo[0].VertexPairCount = (uint8_t)(LengthOfArray(Tails_UpperArmIndices_DC) / 2);
	TailsWeldInfo[0].WeldType = 2;
	TailsWeldInfo[0].VertIndexes = Tails_UpperArmIndices_DC;
	TailsWeldInfo[1].BaseModel = *MILES_OBJECTS;
	TailsWeldInfo[1].ModelA = MILES_OBJECTS[21];
	TailsWeldInfo[1].ModelB = MILES_OBJECTS[22];
	TailsWeldInfo[1].VertexPairCount = (uint8_t)(LengthOfArray(Tails_LowerArmIndices_DC) / 2);
	TailsWeldInfo[1].WeldType = 2;
	TailsWeldInfo[1].anonymous_5 = 0;
	TailsWeldInfo[1].VertexBuffer = 0;
	TailsWeldInfo[1].VertIndexes = Tails_LowerArmIndices_DC;
	TailsWeldInfo[2].BaseModel = *MILES_OBJECTS;
	TailsWeldInfo[2].ModelA = MILES_OBJECTS[23];
	v0 = MILES_OBJECTS[24];
	TailsWeldInfo[2].VertIndexes = Tails_UpperArmIndices_DC;
	TailsWeldInfo[2].ModelB = v0;
	TailsWeldInfo[2].VertexPairCount = (uint8_t)(LengthOfArray(Tails_UpperArmIndices_DC) / 2);
	TailsWeldInfo[2].WeldType = 2;
	TailsWeldInfo[2].anonymous_5 = 0;
	TailsWeldInfo[2].VertexBuffer = 0;
	TailsWeldInfo[3].BaseModel = *MILES_OBJECTS;
	TailsWeldInfo[3].ModelA = MILES_OBJECTS[24];
	TailsWeldInfo[3].ModelB = MILES_OBJECTS[25];
	TailsWeldInfo[3].VertexPairCount = (uint8_t)(LengthOfArray(Tails_LowerArmIndices_DC) / 2);
	TailsWeldInfo[3].WeldType = 2;
	TailsWeldInfo[3].anonymous_5 = 0;
	TailsWeldInfo[3].VertexBuffer = 0;
	TailsWeldInfo[3].VertIndexes = Tails_LowerArmIndices_DC;
	TailsWeldInfo[4].BaseModel = *MILES_OBJECTS;
	TailsWeldInfo[4].ModelA = MILES_OBJECTS[26];
	TailsWeldInfo[4].ModelB = MILES_OBJECTS[27];
	TailsWeldInfo[4].VertexPairCount = (uint8_t)(LengthOfArray(Tails_LegIndices_DC) / 2);
	TailsWeldInfo[4].WeldType = 2;
	TailsWeldInfo[4].anonymous_5 = 0;
	TailsWeldInfo[4].VertexBuffer = 0;
	TailsWeldInfo[4].VertIndexes = Tails_LegIndices_DC;
	TailsWeldInfo[5].BaseModel = *MILES_OBJECTS;
	TailsWeldInfo[5].ModelA = MILES_OBJECTS[27];
	TailsWeldInfo[5].ModelB = MILES_OBJECTS[28];
	TailsWeldInfo[5].VertexPairCount = (uint8_t)(LengthOfArray(Tails_LegIndices_DC) / 2);
	TailsWeldInfo[5].WeldType = 2;
	TailsWeldInfo[5].anonymous_5 = 0;
	TailsWeldInfo[5].VertexBuffer = 0;
	TailsWeldInfo[5].VertIndexes = Tails_LegIndices_DC;
	TailsWeldInfo[6].BaseModel = *MILES_OBJECTS;
	TailsWeldInfo[6].ModelA = MILES_OBJECTS[29];
	TailsWeldInfo[6].ModelB = MILES_OBJECTS[30];
	TailsWeldInfo[6].VertexPairCount = (uint8_t)(LengthOfArray(Tails_LegIndices_DC) / 2);
	TailsWeldInfo[6].WeldType = 2;
	TailsWeldInfo[6].anonymous_5 = 0;
	TailsWeldInfo[6].VertexBuffer = 0;
	TailsWeldInfo[6].VertIndexes = Tails_LegIndices_DC;
	TailsWeldInfo[7].BaseModel = *MILES_OBJECTS;
	TailsWeldInfo[7].ModelA = MILES_OBJECTS[30];
	TailsWeldInfo[7].ModelB = MILES_OBJECTS[31];
	TailsWeldInfo[7].VertexPairCount = (uint8_t)(LengthOfArray(Tails_LegIndices_DC) / 2);
	TailsWeldInfo[7].WeldType = 2;
	TailsWeldInfo[7].anonymous_5 = 0;
	TailsWeldInfo[7].VertexBuffer = 0;
	TailsWeldInfo[7].VertIndexes = Tails_LegIndices_DC;
	TailsWeldInfo[8].BaseModel = *MILES_OBJECTS;
	TailsWeldInfo[8].ModelA = MILES_OBJECTS[32];
	TailsWeldInfo[8].ModelB = MILES_OBJECTS[33];
	TailsWeldInfo[8].VertexPairCount = (uint8_t)(LengthOfArray(Tails_ShoeIndices_DC) / 2);
	TailsWeldInfo[8].WeldType = 2;
	TailsWeldInfo[8].anonymous_5 = 0;
	TailsWeldInfo[8].VertexBuffer = 0;
	TailsWeldInfo[8].VertIndexes = Tails_ShoeIndices_DC;
	TailsWeldInfo[9].BaseModel = *MILES_OBJECTS;
	TailsWeldInfo[9].ModelA = MILES_OBJECTS[34];
	v1 = MILES_OBJECTS[35];
	TailsWeldInfo[9].VertIndexes = Tails_ShoeIndices_DC;
	TailsWeldInfo[9].ModelB = v1;
	TailsWeldInfo[9].VertexPairCount = (uint8_t)(LengthOfArray(Tails_ShoeIndices_DC) / 2);
	TailsWeldInfo[9].WeldType = 2;
	TailsWeldInfo[9].anonymous_5 = 0;
	TailsWeldInfo[9].VertexBuffer = 0;
	TailsWeldInfo[10].BaseModel = *MILES_OBJECTS;
	TailsWeldInfo[10].ModelA = MILES_OBJECTS[36];
	TailsWeldInfo[10].ModelB = MILES_OBJECTS[37];
	TailsWeldInfo[10].VertexPairCount = (uint8_t)(LengthOfArray(Tails_HandIndices_DC) / 2);
	TailsWeldInfo[10].WeldType = 2;
	TailsWeldInfo[10].anonymous_5 = 0;
	TailsWeldInfo[10].VertexBuffer = 0;
	TailsWeldInfo[10].VertIndexes = Tails_HandIndices_DC;
	TailsWeldInfo[11].BaseModel = *MILES_OBJECTS;
	TailsWeldInfo[11].ModelA = MILES_OBJECTS[38];
	TailsWeldInfo[11].ModelB = MILES_OBJECTS[39];
	TailsWeldInfo[11].VertexPairCount = (uint8_t)(LengthOfArray(Tails_HandIndices_DC) / 2);
	TailsWeldInfo[11].WeldType = 2;
	TailsWeldInfo[11].anonymous_5 = 0;
	TailsWeldInfo[11].VertexBuffer = 0;
	TailsWeldInfo[11].VertIndexes = Tails_HandIndices_DC;
	TailsWeldInfo[12].BaseModel = MILES_OBJECTS[1];
	TailsWeldInfo[12].ModelA = MILES_OBJECTS[40];
	TailsWeldInfo[12].ModelB = MILES_OBJECTS[41];
	TailsWeldInfo[12].VertexPairCount = (uint8_t)(LengthOfArray(Tails_UpperArmIndices_DC) / 2);
	TailsWeldInfo[12].WeldType = 2;
	TailsWeldInfo[12].anonymous_5 = 0;
	TailsWeldInfo[12].VertexBuffer = 0;
	TailsWeldInfo[12].VertIndexes = Tails_UpperArmIndices_DC;
	TailsWeldInfo[13].BaseModel = MILES_OBJECTS[1];
	TailsWeldInfo[13].ModelA = MILES_OBJECTS[41];
	TailsWeldInfo[13].ModelB = MILES_OBJECTS[42];
	TailsWeldInfo[13].VertexPairCount = (uint8_t)(LengthOfArray(Tails_LowerArmIndices_DC) / 2);
	TailsWeldInfo[13].WeldType = 2;
	TailsWeldInfo[13].anonymous_5 = 0;
	TailsWeldInfo[13].VertexBuffer = 0;
	TailsWeldInfo[13].VertIndexes = Tails_LowerArmIndices_DC;
	TailsWeldInfo[14].BaseModel = MILES_OBJECTS[1];
	TailsWeldInfo[14].ModelA = MILES_OBJECTS[43];
	TailsWeldInfo[14].ModelB = MILES_OBJECTS[44];
	TailsWeldInfo[14].VertexPairCount = (uint8_t)(LengthOfArray(Tails_UpperArmIndices_DC) / 2);
	TailsWeldInfo[14].WeldType = 2;
	TailsWeldInfo[14].anonymous_5 = 0;
	TailsWeldInfo[14].VertexBuffer = 0;
	TailsWeldInfo[14].VertIndexes = Tails_UpperArmIndices_DC;
	TailsWeldInfo[15].BaseModel = MILES_OBJECTS[1];
	TailsWeldInfo[15].ModelA = MILES_OBJECTS[44];
	TailsWeldInfo[15].ModelB = MILES_OBJECTS[45];
	TailsWeldInfo[15].VertexPairCount = (uint8_t)(LengthOfArray(Tails_LowerArmIndices_DC) / 2);
	TailsWeldInfo[15].WeldType = 2;
	TailsWeldInfo[15].anonymous_5 = 0;
	TailsWeldInfo[15].VertexBuffer = 0;
	TailsWeldInfo[15].VertIndexes = Tails_LowerArmIndices_DC;
	TailsWeldInfo[16].BaseModel = MILES_OBJECTS[1];
	TailsWeldInfo[16].ModelA = MILES_OBJECTS[46];
	TailsWeldInfo[16].ModelB = MILES_OBJECTS[47];
	TailsWeldInfo[16].VertexPairCount = (uint8_t)(LengthOfArray(Tails_LegIndices_DC) / 2);
	TailsWeldInfo[16].WeldType = 2;
	TailsWeldInfo[16].anonymous_5 = 0;
	TailsWeldInfo[16].VertexBuffer = 0;
	TailsWeldInfo[16].VertIndexes = Tails_LegIndices_DC;
	TailsWeldInfo[17].BaseModel = MILES_OBJECTS[1];
	TailsWeldInfo[17].ModelA = MILES_OBJECTS[47];
	TailsWeldInfo[17].ModelB = MILES_OBJECTS[48];
	TailsWeldInfo[17].VertexPairCount = (uint8_t)(LengthOfArray(Tails_LegIndices_DC) / 2);
	TailsWeldInfo[17].WeldType = 2;
	TailsWeldInfo[17].anonymous_5 = 0;
	TailsWeldInfo[17].VertexBuffer = 0;
	TailsWeldInfo[17].VertIndexes = Tails_LegIndices_DC;
	TailsWeldInfo[18].BaseModel = MILES_OBJECTS[1];
	TailsWeldInfo[18].ModelA = MILES_OBJECTS[49];
	TailsWeldInfo[18].ModelB = MILES_OBJECTS[50];
	TailsWeldInfo[18].VertexPairCount = (uint8_t)(LengthOfArray(Tails_LegIndices_DC) / 2);
	TailsWeldInfo[18].WeldType = 2;
	TailsWeldInfo[18].anonymous_5 = 0;
	TailsWeldInfo[18].VertexBuffer = 0;
	TailsWeldInfo[18].VertIndexes = Tails_LegIndices_DC;
	TailsWeldInfo[19].BaseModel = MILES_OBJECTS[1];
	TailsWeldInfo[19].ModelA = MILES_OBJECTS[50];
	v2 = MILES_OBJECTS[51];
	TailsWeldInfo[19].VertIndexes = Tails_LegIndices_DC;
	TailsWeldInfo[19].ModelB = v2;
	TailsWeldInfo[19].VertexPairCount = (uint8_t)(LengthOfArray(Tails_LegIndices_DC) / 2);
	TailsWeldInfo[19].WeldType = 2;
	TailsWeldInfo[19].anonymous_5 = 0;
	TailsWeldInfo[19].VertexBuffer = 0;
	TailsWeldInfo[20].BaseModel = MILES_OBJECTS[1];
	TailsWeldInfo[20].ModelA = MILES_OBJECTS[52];
	TailsWeldInfo[20].ModelB = MILES_OBJECTS[53];
	TailsWeldInfo[20].VertexPairCount = (uint8_t)(LengthOfArray(Tails_ShoeIndices_DC) / 2);
	TailsWeldInfo[20].WeldType = 2;
	TailsWeldInfo[20].anonymous_5 = 0;
	TailsWeldInfo[20].VertexBuffer = 0;
	TailsWeldInfo[20].VertIndexes = Tails_ShoeIndices_DC;
	TailsWeldInfo[21].BaseModel = MILES_OBJECTS[1];
	TailsWeldInfo[21].ModelA = MILES_OBJECTS[54];
	TailsWeldInfo[21].ModelB = MILES_OBJECTS[55];
	TailsWeldInfo[21].VertexPairCount = (uint8_t)(LengthOfArray(Tails_ShoeIndices_DC) / 2);
	TailsWeldInfo[21].WeldType = 2;
	TailsWeldInfo[21].anonymous_5 = 0;
	TailsWeldInfo[21].VertexBuffer = 0;
	TailsWeldInfo[21].VertIndexes = Tails_ShoeIndices_DC;
	TailsWeldInfo[22].BaseModel = MILES_OBJECTS[1];
	TailsWeldInfo[22].ModelA = MILES_OBJECTS[56];
	TailsWeldInfo[22].ModelB = MILES_OBJECTS[57];
	TailsWeldInfo[22].VertexPairCount = (uint8_t)(LengthOfArray(Tails_HandIndices_DC) / 2);
	TailsWeldInfo[22].WeldType = 2;
	TailsWeldInfo[22].anonymous_5 = 0;
	TailsWeldInfo[22].VertexBuffer = 0;
	TailsWeldInfo[22].VertIndexes = Tails_HandIndices_DC;
	TailsWeldInfo[23].BaseModel = MILES_OBJECTS[1];
	TailsWeldInfo[23].ModelA = MILES_OBJECTS[58];
	TailsWeldInfo[23].ModelB = MILES_OBJECTS[59];
	TailsWeldInfo[23].VertexPairCount = (uint8_t)(LengthOfArray(Tails_HandIndices_DC) / 2);
	TailsWeldInfo[23].WeldType = 2;
	TailsWeldInfo[23].anonymous_5 = 0;
	TailsWeldInfo[23].VertexBuffer = 0;
	TailsWeldInfo[23].VertIndexes = Tails_HandIndices_DC;
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
	NPCTailsWeldInfo[0].VertexPairCount = (uint8_t)(LengthOfArray(Tails_UpperArmIndices_DC) / 2);
	NPCTailsWeldInfo[0].WeldType = 2;
	NPCTailsWeldInfo[0].VertIndexes = Tails_UpperArmIndices_DC;
	NPCTailsWeldInfo[1].BaseModel = *MILES_OBJECTS;
	NPCTailsWeldInfo[1].ModelA = MILES_OBJECTS[21];
	NPCTailsWeldInfo[1].ModelB = MILES_OBJECTS[22];
	NPCTailsWeldInfo[1].VertexPairCount = (uint8_t)(LengthOfArray(Tails_LowerArmIndices_DC) / 2);
	NPCTailsWeldInfo[1].WeldType = 2;
	NPCTailsWeldInfo[1].anonymous_5 = 0;
	NPCTailsWeldInfo[1].VertexBuffer = 0;
	NPCTailsWeldInfo[1].VertIndexes = Tails_LowerArmIndices_DC;
	NPCTailsWeldInfo[2].BaseModel = *MILES_OBJECTS;
	NPCTailsWeldInfo[2].ModelA = MILES_OBJECTS[23];
	v0 = MILES_OBJECTS[24];
	NPCTailsWeldInfo[2].VertIndexes = Tails_UpperArmIndices_DC;
	NPCTailsWeldInfo[2].ModelB = v0;
	NPCTailsWeldInfo[2].VertexPairCount = (uint8_t)(LengthOfArray(Tails_UpperArmIndices_DC) / 2);
	NPCTailsWeldInfo[2].WeldType = 2;
	NPCTailsWeldInfo[2].anonymous_5 = 0;
	NPCTailsWeldInfo[2].VertexBuffer = 0;
	NPCTailsWeldInfo[3].BaseModel = *MILES_OBJECTS;
	NPCTailsWeldInfo[3].ModelA = MILES_OBJECTS[24];
	NPCTailsWeldInfo[3].ModelB = MILES_OBJECTS[25];
	NPCTailsWeldInfo[3].VertexPairCount = (uint8_t)(LengthOfArray(Tails_LowerArmIndices_DC) / 2);
	NPCTailsWeldInfo[3].WeldType = 2;
	NPCTailsWeldInfo[3].anonymous_5 = 0;
	NPCTailsWeldInfo[3].VertexBuffer = 0;
	NPCTailsWeldInfo[3].VertIndexes = Tails_LowerArmIndices_DC;
	NPCTailsWeldInfo[4].BaseModel = *MILES_OBJECTS;
	NPCTailsWeldInfo[4].ModelA = MILES_OBJECTS[26];
	NPCTailsWeldInfo[4].ModelB = MILES_OBJECTS[27];
	NPCTailsWeldInfo[4].VertexPairCount = (uint8_t)(LengthOfArray(Tails_LegIndices_DC) / 2);
	NPCTailsWeldInfo[4].WeldType = 2;
	NPCTailsWeldInfo[4].anonymous_5 = 0;
	NPCTailsWeldInfo[4].VertexBuffer = 0;
	NPCTailsWeldInfo[4].VertIndexes = Tails_LegIndices_DC;
	NPCTailsWeldInfo[5].BaseModel = *MILES_OBJECTS;
	NPCTailsWeldInfo[5].ModelA = MILES_OBJECTS[27];
	NPCTailsWeldInfo[5].ModelB = MILES_OBJECTS[28];
	NPCTailsWeldInfo[5].VertexPairCount = (uint8_t)(LengthOfArray(Tails_LegIndices_DC) / 2);
	NPCTailsWeldInfo[5].WeldType = 2;
	NPCTailsWeldInfo[5].anonymous_5 = 0;
	NPCTailsWeldInfo[5].VertexBuffer = 0;
	NPCTailsWeldInfo[5].VertIndexes = Tails_LegIndices_DC;
	NPCTailsWeldInfo[6].BaseModel = *MILES_OBJECTS;
	NPCTailsWeldInfo[6].ModelA = MILES_OBJECTS[29];
	NPCTailsWeldInfo[6].ModelB = MILES_OBJECTS[30];
	NPCTailsWeldInfo[6].VertexPairCount = (uint8_t)(LengthOfArray(Tails_LegIndices_DC) / 2);
	NPCTailsWeldInfo[6].WeldType = 2;
	NPCTailsWeldInfo[6].anonymous_5 = 0;
	NPCTailsWeldInfo[6].VertexBuffer = 0;
	NPCTailsWeldInfo[6].VertIndexes = Tails_LegIndices_DC;
	NPCTailsWeldInfo[7].BaseModel = *MILES_OBJECTS;
	NPCTailsWeldInfo[7].ModelA = MILES_OBJECTS[30];
	NPCTailsWeldInfo[7].ModelB = MILES_OBJECTS[31];
	NPCTailsWeldInfo[7].VertexPairCount = (uint8_t)(LengthOfArray(Tails_LegIndices_DC) / 2);
	NPCTailsWeldInfo[7].WeldType = 2;
	NPCTailsWeldInfo[7].anonymous_5 = 0;
	NPCTailsWeldInfo[7].VertexBuffer = 0;
	NPCTailsWeldInfo[7].VertIndexes = Tails_LegIndices_DC;
	NPCTailsWeldInfo[8].BaseModel = *MILES_OBJECTS;
	NPCTailsWeldInfo[8].ModelA = MILES_OBJECTS[32];
	NPCTailsWeldInfo[8].ModelB = MILES_OBJECTS[33];
	NPCTailsWeldInfo[8].VertexPairCount = (uint8_t)(LengthOfArray(Tails_ShoeIndices_DC) / 2);
	NPCTailsWeldInfo[8].WeldType = 2;
	NPCTailsWeldInfo[8].anonymous_5 = 0;
	NPCTailsWeldInfo[8].VertexBuffer = 0;
	NPCTailsWeldInfo[8].VertIndexes = Tails_ShoeIndices_DC;
	NPCTailsWeldInfo[9].BaseModel = *MILES_OBJECTS;
	NPCTailsWeldInfo[9].ModelA = MILES_OBJECTS[34];
	v1 = MILES_OBJECTS[35];
	NPCTailsWeldInfo[9].VertIndexes = Tails_ShoeIndices_DC;
	NPCTailsWeldInfo[9].ModelB = v1;
	NPCTailsWeldInfo[9].VertexPairCount = (uint8_t)(LengthOfArray(Tails_ShoeIndices_DC) / 2);
	NPCTailsWeldInfo[9].WeldType = 2;
	NPCTailsWeldInfo[9].anonymous_5 = 0;
	NPCTailsWeldInfo[9].VertexBuffer = 0;
	NPCTailsWeldInfo[10].BaseModel = *MILES_OBJECTS;
	NPCTailsWeldInfo[10].ModelA = MILES_OBJECTS[36];
	NPCTailsWeldInfo[10].ModelB = MILES_OBJECTS[37];
	NPCTailsWeldInfo[10].VertexPairCount = (uint8_t)(LengthOfArray(Tails_HandIndices_DC) / 2);
	NPCTailsWeldInfo[10].WeldType = 2;
	NPCTailsWeldInfo[10].anonymous_5 = 0;
	NPCTailsWeldInfo[10].VertexBuffer = 0;
	NPCTailsWeldInfo[10].VertIndexes = Tails_HandIndices_DC;
	NPCTailsWeldInfo[11].BaseModel = *MILES_OBJECTS;
	NPCTailsWeldInfo[11].ModelA = MILES_OBJECTS[38];
	NPCTailsWeldInfo[11].ModelB = MILES_OBJECTS[39];
	NPCTailsWeldInfo[11].VertexPairCount = (uint8_t)(LengthOfArray(Tails_HandIndices_DC) / 2);
	NPCTailsWeldInfo[11].WeldType = 2;
	NPCTailsWeldInfo[11].anonymous_5 = 0;
	NPCTailsWeldInfo[11].VertexBuffer = 0;
	NPCTailsWeldInfo[11].VertIndexes = Tails_HandIndices_DC;
	NPCTailsWeldInfo[12].BaseModel = MILES_OBJECTS[1];
	NPCTailsWeldInfo[12].ModelA = MILES_OBJECTS[40];
	NPCTailsWeldInfo[12].ModelB = MILES_OBJECTS[41];
	NPCTailsWeldInfo[12].VertexPairCount = (uint8_t)(LengthOfArray(Tails_UpperArmIndices_DC) / 2);
	NPCTailsWeldInfo[12].WeldType = 2;
	NPCTailsWeldInfo[12].anonymous_5 = 0;
	NPCTailsWeldInfo[12].VertexBuffer = 0;
	NPCTailsWeldInfo[12].VertIndexes = Tails_UpperArmIndices_DC;
	NPCTailsWeldInfo[13].BaseModel = MILES_OBJECTS[1];
	NPCTailsWeldInfo[13].ModelA = MILES_OBJECTS[41];
	NPCTailsWeldInfo[13].ModelB = MILES_OBJECTS[42];
	NPCTailsWeldInfo[13].VertexPairCount = (uint8_t)(LengthOfArray(Tails_LowerArmIndices_DC) / 2);
	NPCTailsWeldInfo[13].WeldType = 2;
	NPCTailsWeldInfo[13].anonymous_5 = 0;
	NPCTailsWeldInfo[13].VertexBuffer = 0;
	NPCTailsWeldInfo[13].VertIndexes = Tails_LowerArmIndices_DC;
	NPCTailsWeldInfo[14].BaseModel = MILES_OBJECTS[1];
	NPCTailsWeldInfo[14].ModelA = MILES_OBJECTS[43];
	NPCTailsWeldInfo[14].ModelB = MILES_OBJECTS[44];
	NPCTailsWeldInfo[14].VertexPairCount = (uint8_t)(LengthOfArray(Tails_UpperArmIndices_DC) / 2);
	NPCTailsWeldInfo[14].WeldType = 2;
	NPCTailsWeldInfo[14].anonymous_5 = 0;
	NPCTailsWeldInfo[14].VertexBuffer = 0;
	NPCTailsWeldInfo[14].VertIndexes = Tails_UpperArmIndices_DC;
	NPCTailsWeldInfo[15].BaseModel = MILES_OBJECTS[1];
	NPCTailsWeldInfo[15].ModelA = MILES_OBJECTS[44];
	NPCTailsWeldInfo[15].ModelB = MILES_OBJECTS[45];
	NPCTailsWeldInfo[15].VertexPairCount = (uint8_t)(LengthOfArray(Tails_LowerArmIndices_DC) / 2);
	NPCTailsWeldInfo[15].WeldType = 2;
	NPCTailsWeldInfo[15].anonymous_5 = 0;
	NPCTailsWeldInfo[15].VertexBuffer = 0;
	NPCTailsWeldInfo[15].VertIndexes = Tails_LowerArmIndices_DC;
	NPCTailsWeldInfo[16].BaseModel = MILES_OBJECTS[1];
	NPCTailsWeldInfo[16].ModelA = MILES_OBJECTS[46];
	NPCTailsWeldInfo[16].ModelB = MILES_OBJECTS[47];
	NPCTailsWeldInfo[16].VertexPairCount = (uint8_t)(LengthOfArray(Tails_LegIndices_DC) / 2);
	NPCTailsWeldInfo[16].WeldType = 2;
	NPCTailsWeldInfo[16].anonymous_5 = 0;
	NPCTailsWeldInfo[16].VertexBuffer = 0;
	NPCTailsWeldInfo[16].VertIndexes = Tails_LegIndices_DC;
	NPCTailsWeldInfo[17].BaseModel = MILES_OBJECTS[1];
	NPCTailsWeldInfo[17].ModelA = MILES_OBJECTS[47];
	NPCTailsWeldInfo[17].ModelB = MILES_OBJECTS[48];
	NPCTailsWeldInfo[17].VertexPairCount = (uint8_t)(LengthOfArray(Tails_LegIndices_DC) / 2);
	NPCTailsWeldInfo[17].WeldType = 2;
	NPCTailsWeldInfo[17].anonymous_5 = 0;
	NPCTailsWeldInfo[17].VertexBuffer = 0;
	NPCTailsWeldInfo[17].VertIndexes = Tails_LegIndices_DC;
	NPCTailsWeldInfo[18].BaseModel = MILES_OBJECTS[1];
	NPCTailsWeldInfo[18].ModelA = MILES_OBJECTS[49];
	NPCTailsWeldInfo[18].ModelB = MILES_OBJECTS[50];
	NPCTailsWeldInfo[18].VertexPairCount = (uint8_t)(LengthOfArray(Tails_LegIndices_DC) / 2);
	NPCTailsWeldInfo[18].WeldType = 2;
	NPCTailsWeldInfo[18].anonymous_5 = 0;
	NPCTailsWeldInfo[18].VertexBuffer = 0;
	NPCTailsWeldInfo[18].VertIndexes = Tails_LegIndices_DC;
	NPCTailsWeldInfo[19].BaseModel = MILES_OBJECTS[1];
	NPCTailsWeldInfo[19].ModelA = MILES_OBJECTS[50];
	v2 = MILES_OBJECTS[51];
	NPCTailsWeldInfo[19].anonymous_5 = 0;
	NPCTailsWeldInfo[19].VertexBuffer = 0;
	NPCTailsWeldInfo[19].VertIndexes = Tails_LegIndices_DC;
	NPCTailsWeldInfo[19].ModelB = v2;
	NPCTailsWeldInfo[19].VertexPairCount = (uint8_t)(LengthOfArray(Tails_LegIndices_DC) / 2);
	NPCTailsWeldInfo[19].WeldType = 2;
	NPCTailsWeldInfo[20].BaseModel = MILES_OBJECTS[1];
	NPCTailsWeldInfo[20].ModelA = MILES_OBJECTS[52];
	NPCTailsWeldInfo[20].ModelB = MILES_OBJECTS[53];
	NPCTailsWeldInfo[20].anonymous_5 = 0;
	NPCTailsWeldInfo[20].VertexBuffer = 0;
	NPCTailsWeldInfo[20].VertexPairCount = (uint8_t)(LengthOfArray(Tails_ShoeIndices_DC) / 2);
	NPCTailsWeldInfo[20].WeldType = 2;
	NPCTailsWeldInfo[20].VertIndexes = Tails_ShoeIndices_DC;
	NPCTailsWeldInfo[21].BaseModel = MILES_OBJECTS[1];
	NPCTailsWeldInfo[21].ModelA = MILES_OBJECTS[54];
	v3 = MILES_OBJECTS[55];
	NPCTailsWeldInfo[21].anonymous_5 = 0;
	NPCTailsWeldInfo[21].VertexBuffer = 0;
	NPCTailsWeldInfo[21].ModelB = v3;
	NPCTailsWeldInfo[21].VertIndexes = Tails_ShoeIndices_DC;
	NPCTailsWeldInfo[21].VertexPairCount = (uint8_t)(LengthOfArray(Tails_ShoeIndices_DC) / 2);
	NPCTailsWeldInfo[21].WeldType = 2;
	NPCTailsWeldInfo[22].BaseModel = MILES_OBJECTS[1];
	NPCTailsWeldInfo[22].ModelA = MILES_OBJECTS[56];
	v4 = MILES_OBJECTS[57];
	NPCTailsWeldInfo[22].anonymous_5 = 0;
	NPCTailsWeldInfo[22].VertexBuffer = 0;
	NPCTailsWeldInfo[22].ModelB = v4;
	NPCTailsWeldInfo[22].VertIndexes = Tails_HandIndices_DC;
	NPCTailsWeldInfo[22].VertexPairCount = (uint8_t)(LengthOfArray(Tails_HandIndices_DC) / 2);
	NPCTailsWeldInfo[22].WeldType = 2;
	NPCTailsWeldInfo[23].BaseModel = MILES_OBJECTS[1];
	NPCTailsWeldInfo[23].ModelA = MILES_OBJECTS[58];
	v5 = MILES_OBJECTS[59];
	NPCTailsWeldInfo[23].anonymous_5 = 0;
	NPCTailsWeldInfo[23].VertexBuffer = 0;
	NPCTailsWeldInfo[24].BaseModel = 0;
	NPCTailsWeldInfo[24].ModelA = 0;
	NPCTailsWeldInfo[23].VertIndexes = Tails_HandIndices_DC;
	NPCTailsWeldInfo[24].ModelB = 0;
	NPCTailsWeldInfo[24].VertexPairCount = 0;
	NPCTailsWeldInfo[24].VertexBuffer = 0;
	NPCTailsWeldInfo[23].ModelB = v5;
	NPCTailsWeldInfo[23].VertexPairCount = (uint8_t)(LengthOfArray(Tails_HandIndices_DC) / 2);
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
	KnucklesWeldInfo[0].VertexPairCount = (uint8_t)(LengthOfArray(Knuckles_UpperArmIndices_DC) / 2);
	KnucklesWeldInfo[0].WeldType = 2;
	KnucklesWeldInfo[0].VertIndexes = Knuckles_UpperArmIndices_DC;
	KnucklesWeldInfo[1].BaseModel = *KNUCKLES_OBJECTS;
	KnucklesWeldInfo[1].ModelA = KNUCKLES_OBJECTS[3];
	KnucklesWeldInfo[1].ModelB = KNUCKLES_OBJECTS[4];
	KnucklesWeldInfo[1].VertexPairCount = (uint8_t)(LengthOfArray(Knuckles_LowerArmIndices_DC) / 2);
	KnucklesWeldInfo[1].WeldType = 2;
	KnucklesWeldInfo[1].anonymous_5 = 0;
	KnucklesWeldInfo[1].VertexBuffer = 0;
	KnucklesWeldInfo[1].VertIndexes = Knuckles_LowerArmIndices_DC;
	KnucklesWeldInfo[2].BaseModel = *KNUCKLES_OBJECTS;
	KnucklesWeldInfo[2].ModelA = KNUCKLES_OBJECTS[6];
	v0 = KNUCKLES_OBJECTS[7];
	KnucklesWeldInfo[2].VertIndexes = Knuckles_UpperArmIndices_DC;
	KnucklesWeldInfo[2].ModelB = v0;
	KnucklesWeldInfo[2].VertexPairCount = (uint8_t)(LengthOfArray(Knuckles_UpperArmIndices_DC) / 2);
	KnucklesWeldInfo[2].WeldType = 2;
	KnucklesWeldInfo[2].anonymous_5 = 0;
	KnucklesWeldInfo[2].VertexBuffer = 0;
	KnucklesWeldInfo[3].BaseModel = *KNUCKLES_OBJECTS;
	KnucklesWeldInfo[3].ModelA = KNUCKLES_OBJECTS[7];
	KnucklesWeldInfo[3].ModelB = KNUCKLES_OBJECTS[8];
	KnucklesWeldInfo[3].VertexPairCount = (uint8_t)(LengthOfArray(Knuckles_LowerArmIndices_DC) / 2);
	KnucklesWeldInfo[3].WeldType = 2;
	KnucklesWeldInfo[3].anonymous_5 = 0;
	KnucklesWeldInfo[3].VertexBuffer = 0;
	KnucklesWeldInfo[3].VertIndexes = Knuckles_LowerArmIndices_DC;
	KnucklesWeldInfo[4].BaseModel = *KNUCKLES_OBJECTS;
	KnucklesWeldInfo[4].ModelA = KNUCKLES_OBJECTS[10];
	KnucklesWeldInfo[4].ModelB = KNUCKLES_OBJECTS[11];
	KnucklesWeldInfo[4].VertexPairCount = (uint8_t)(LengthOfArray(Knuckles_LegIndices_DC) / 2);
	KnucklesWeldInfo[4].WeldType = 2;
	KnucklesWeldInfo[4].anonymous_5 = 0;
	KnucklesWeldInfo[4].VertexBuffer = 0;
	KnucklesWeldInfo[4].VertIndexes = Knuckles_LegIndices_DC;
	KnucklesWeldInfo[5].BaseModel = *KNUCKLES_OBJECTS;
	KnucklesWeldInfo[5].ModelA = KNUCKLES_OBJECTS[11];
	KnucklesWeldInfo[5].ModelB = KNUCKLES_OBJECTS[12];
	KnucklesWeldInfo[5].VertexPairCount = (uint8_t)(LengthOfArray(Knuckles_LegIndices_DC) / 2);
	KnucklesWeldInfo[5].WeldType = 2;
	KnucklesWeldInfo[5].anonymous_5 = 0;
	KnucklesWeldInfo[5].VertexBuffer = 0;
	KnucklesWeldInfo[5].VertIndexes = Knuckles_LegIndices_DC;
	KnucklesWeldInfo[6].BaseModel = *KNUCKLES_OBJECTS;
	KnucklesWeldInfo[6].ModelA = KNUCKLES_OBJECTS[13];
	KnucklesWeldInfo[6].ModelB = KNUCKLES_OBJECTS[14];
	KnucklesWeldInfo[6].VertexPairCount = (uint8_t)(LengthOfArray(Knuckles_LegIndices_DC) / 2);
	KnucklesWeldInfo[6].WeldType = 2;
	KnucklesWeldInfo[6].anonymous_5 = 0;
	KnucklesWeldInfo[6].VertexBuffer = 0;
	KnucklesWeldInfo[6].VertIndexes = Knuckles_LegIndices_DC;
	KnucklesWeldInfo[7].BaseModel = *KNUCKLES_OBJECTS;
	KnucklesWeldInfo[7].ModelA = KNUCKLES_OBJECTS[14];
	KnucklesWeldInfo[7].ModelB = KNUCKLES_OBJECTS[15];
	KnucklesWeldInfo[7].VertexPairCount = (uint8_t)(LengthOfArray(Knuckles_LegIndices_DC) / 2);
	KnucklesWeldInfo[7].WeldType = 2;
	KnucklesWeldInfo[7].anonymous_5 = 0;
	KnucklesWeldInfo[7].VertexBuffer = 0;
	KnucklesWeldInfo[7].VertIndexes = Knuckles_LegIndices_DC;
	KnucklesWeldInfo[8].BaseModel = *KNUCKLES_OBJECTS;
	KnucklesWeldInfo[8].ModelA = KNUCKLES_OBJECTS[16];
	KnucklesWeldInfo[8].ModelB = KNUCKLES_OBJECTS[17];
	KnucklesWeldInfo[8].VertexPairCount = (uint8_t)(LengthOfArray(Knuckles_ShoeIndices_DC) / 2);
	KnucklesWeldInfo[8].WeldType = 2;
	KnucklesWeldInfo[8].anonymous_5 = 0;
	KnucklesWeldInfo[8].VertexBuffer = 0;
	KnucklesWeldInfo[8].VertIndexes = Knuckles_ShoeIndices_DC;
	KnucklesWeldInfo[9].BaseModel = *KNUCKLES_OBJECTS;
	KnucklesWeldInfo[9].ModelA = KNUCKLES_OBJECTS[18];
	v1 = KNUCKLES_OBJECTS[19];
	KnucklesWeldInfo[9].VertIndexes = Knuckles_ShoeIndices_DC;
	KnucklesWeldInfo[9].ModelB = v1;
	KnucklesWeldInfo[9].VertexPairCount = (uint8_t)(LengthOfArray(Knuckles_ShoeIndices_DC) / 2);
	KnucklesWeldInfo[9].WeldType = 2;
	KnucklesWeldInfo[9].anonymous_5 = 0;
	KnucklesWeldInfo[9].VertexBuffer = 0;
	KnucklesWeldInfo[10].BaseModel = *KNUCKLES_OBJECTS;
	KnucklesWeldInfo[10].ModelA = KNUCKLES_OBJECTS[20];
	KnucklesWeldInfo[10].ModelB = KNUCKLES_OBJECTS[5];
	KnucklesWeldInfo[10].VertexPairCount = (uint8_t)(LengthOfArray(Knuckles_HandIndices_DC) / 2);
	KnucklesWeldInfo[10].WeldType = 2;
	KnucklesWeldInfo[10].anonymous_5 = 0;
	KnucklesWeldInfo[10].VertexBuffer = 0;
	KnucklesWeldInfo[10].VertIndexes = Knuckles_HandIndices_DC;
	KnucklesWeldInfo[11].BaseModel = *KNUCKLES_OBJECTS;
	KnucklesWeldInfo[11].ModelA = KNUCKLES_OBJECTS[22];
	KnucklesWeldInfo[11].ModelB = KNUCKLES_OBJECTS[9];
	KnucklesWeldInfo[11].VertexPairCount = (uint8_t)(LengthOfArray(Knuckles_HandIndices_DC) / 2);
	KnucklesWeldInfo[11].WeldType = 2;
	KnucklesWeldInfo[11].anonymous_5 = 0;
	KnucklesWeldInfo[11].VertexBuffer = 0;
	KnucklesWeldInfo[11].VertIndexes = Knuckles_HandIndices_DC;
	KnucklesWeldInfo[12].BaseModel = KNUCKLES_OBJECTS[1];
	KnucklesWeldInfo[12].ModelA = KNUCKLES_OBJECTS[24];
	KnucklesWeldInfo[12].ModelB = KNUCKLES_OBJECTS[25];
	KnucklesWeldInfo[12].VertexPairCount = (uint8_t)(LengthOfArray(Knuckles_UpperArmIndices_DC) / 2);
	KnucklesWeldInfo[12].WeldType = 2;
	KnucklesWeldInfo[12].anonymous_5 = 0;
	KnucklesWeldInfo[12].VertexBuffer = 0;
	KnucklesWeldInfo[12].VertIndexes = Knuckles_UpperArmIndices_DC;
	KnucklesWeldInfo[13].BaseModel = KNUCKLES_OBJECTS[1];
	KnucklesWeldInfo[13].ModelA = KNUCKLES_OBJECTS[25];
	KnucklesWeldInfo[13].ModelB = KNUCKLES_OBJECTS[26];
	KnucklesWeldInfo[13].VertexPairCount = (uint8_t)(LengthOfArray(Knuckles_LowerArmIndices_DC) / 2);
	KnucklesWeldInfo[13].WeldType = 2;
	KnucklesWeldInfo[13].anonymous_5 = 0;
	KnucklesWeldInfo[13].VertexBuffer = 0;
	KnucklesWeldInfo[13].VertIndexes = Knuckles_LowerArmIndices_DC;
	KnucklesWeldInfo[14].BaseModel = KNUCKLES_OBJECTS[1];
	KnucklesWeldInfo[14].ModelA = KNUCKLES_OBJECTS[28];
	KnucklesWeldInfo[14].ModelB = KNUCKLES_OBJECTS[29];
	KnucklesWeldInfo[14].VertexPairCount = (uint8_t)(LengthOfArray(Knuckles_UpperArmIndices_DC) / 2);
	KnucklesWeldInfo[14].WeldType = 2;
	KnucklesWeldInfo[14].anonymous_5 = 0;
	KnucklesWeldInfo[14].VertexBuffer = 0;
	KnucklesWeldInfo[14].VertIndexes = Knuckles_UpperArmIndices_DC;
	KnucklesWeldInfo[15].BaseModel = KNUCKLES_OBJECTS[1];
	KnucklesWeldInfo[15].ModelA = KNUCKLES_OBJECTS[29];
	KnucklesWeldInfo[15].ModelB = KNUCKLES_OBJECTS[30];
	KnucklesWeldInfo[15].VertexPairCount = (uint8_t)(LengthOfArray(Knuckles_LowerArmIndices_DC) / 2);
	KnucklesWeldInfo[15].WeldType = 2;
	KnucklesWeldInfo[15].anonymous_5 = 0;
	KnucklesWeldInfo[15].VertexBuffer = 0;
	KnucklesWeldInfo[15].VertIndexes = Knuckles_LowerArmIndices_DC;
	KnucklesWeldInfo[16].BaseModel = KNUCKLES_OBJECTS[1];
	KnucklesWeldInfo[16].ModelA = KNUCKLES_OBJECTS[32];
	KnucklesWeldInfo[16].ModelB = KNUCKLES_OBJECTS[33];
	KnucklesWeldInfo[16].VertexPairCount = (uint8_t)(LengthOfArray(Knuckles_LegIndices_DC) / 2);
	KnucklesWeldInfo[16].WeldType = 2;
	KnucklesWeldInfo[16].anonymous_5 = 0;
	KnucklesWeldInfo[16].VertexBuffer = 0;
	KnucklesWeldInfo[16].VertIndexes = Knuckles_LegIndices_DC;
	KnucklesWeldInfo[17].BaseModel = KNUCKLES_OBJECTS[1];
	KnucklesWeldInfo[17].ModelA = KNUCKLES_OBJECTS[33];
	KnucklesWeldInfo[17].ModelB = KNUCKLES_OBJECTS[34];
	KnucklesWeldInfo[17].VertexPairCount = (uint8_t)(LengthOfArray(Knuckles_LegIndices_DC) / 2);
	KnucklesWeldInfo[17].WeldType = 2;
	KnucklesWeldInfo[17].anonymous_5 = 0;
	KnucklesWeldInfo[17].VertexBuffer = 0;
	KnucklesWeldInfo[17].VertIndexes = Knuckles_LegIndices_DC;
	KnucklesWeldInfo[18].BaseModel = KNUCKLES_OBJECTS[1];
	KnucklesWeldInfo[18].ModelA = KNUCKLES_OBJECTS[35];
	KnucklesWeldInfo[18].ModelB = KNUCKLES_OBJECTS[36];
	KnucklesWeldInfo[18].VertexPairCount = (uint8_t)(LengthOfArray(Knuckles_LegIndices_DC) / 2);
	KnucklesWeldInfo[18].WeldType = 2;
	KnucklesWeldInfo[18].anonymous_5 = 0;
	KnucklesWeldInfo[18].VertexBuffer = 0;
	KnucklesWeldInfo[18].VertIndexes = Knuckles_LegIndices_DC;
	KnucklesWeldInfo[19].BaseModel = KNUCKLES_OBJECTS[1];
	KnucklesWeldInfo[19].ModelA = KNUCKLES_OBJECTS[36];
	v2 = KNUCKLES_OBJECTS[37];
	KnucklesWeldInfo[19].VertIndexes = Knuckles_LegIndices_DC;
	KnucklesWeldInfo[19].ModelB = v2;
	KnucklesWeldInfo[19].VertexPairCount = (uint8_t)(LengthOfArray(Knuckles_LegIndices_DC) / 2);
	KnucklesWeldInfo[19].WeldType = 2;
	KnucklesWeldInfo[19].anonymous_5 = 0;
	KnucklesWeldInfo[19].VertexBuffer = 0;
	KnucklesWeldInfo[20].BaseModel = KNUCKLES_OBJECTS[1];
	KnucklesWeldInfo[20].ModelA = KNUCKLES_OBJECTS[38];
	KnucklesWeldInfo[20].ModelB = KNUCKLES_OBJECTS[39];
	KnucklesWeldInfo[20].VertexPairCount = (uint8_t)(LengthOfArray(Knuckles_ShoeIndices_DC) / 2);
	KnucklesWeldInfo[20].WeldType = 2;
	KnucklesWeldInfo[20].anonymous_5 = 0;
	KnucklesWeldInfo[20].VertexBuffer = 0;
	KnucklesWeldInfo[20].VertIndexes = Knuckles_ShoeIndices_DC;
	KnucklesWeldInfo[21].BaseModel = KNUCKLES_OBJECTS[1];
	KnucklesWeldInfo[21].ModelA = KNUCKLES_OBJECTS[40];
	KnucklesWeldInfo[21].ModelB = KNUCKLES_OBJECTS[41];
	KnucklesWeldInfo[21].VertexPairCount = (uint8_t)(LengthOfArray(Knuckles_ShoeIndices_DC) / 2);
	KnucklesWeldInfo[21].WeldType = 2;
	KnucklesWeldInfo[21].anonymous_5 = 0;
	KnucklesWeldInfo[21].VertexBuffer = 0;
	KnucklesWeldInfo[21].VertIndexes = Knuckles_ShoeIndices_DC;
	KnucklesWeldInfo[22].BaseModel = KNUCKLES_OBJECTS[1];
	KnucklesWeldInfo[22].ModelA = KNUCKLES_OBJECTS[42];
	KnucklesWeldInfo[22].ModelB = KNUCKLES_OBJECTS[27];
	KnucklesWeldInfo[22].VertexPairCount = (uint8_t)(LengthOfArray(Knuckles_HandIndices_DC) / 2);
	KnucklesWeldInfo[22].WeldType = 2;
	KnucklesWeldInfo[22].anonymous_5 = 0;
	KnucklesWeldInfo[22].VertexBuffer = 0;
	KnucklesWeldInfo[22].VertIndexes = Knuckles_HandIndices_DC;
	KnucklesWeldInfo[23].BaseModel = KNUCKLES_OBJECTS[1];
	KnucklesWeldInfo[23].ModelA = KNUCKLES_OBJECTS[44];
	KnucklesWeldInfo[23].ModelB = KNUCKLES_OBJECTS[31];
	KnucklesWeldInfo[23].VertexPairCount = (uint8_t)(LengthOfArray(Knuckles_HandIndices_DC) / 2);
	KnucklesWeldInfo[23].WeldType = 2;
	KnucklesWeldInfo[23].anonymous_5 = 0;
	KnucklesWeldInfo[23].VertexBuffer = 0;
	KnucklesWeldInfo[23].VertIndexes = Knuckles_HandIndices_DC;
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
	NPCKnucklesWeldInfo[0].VertexPairCount = (uint8_t)(LengthOfArray(Knuckles_UpperArmIndices_DC) / 2);
	NPCKnucklesWeldInfo[0].WeldType = 2;
	NPCKnucklesWeldInfo[0].VertIndexes = Knuckles_UpperArmIndices_DC;
	NPCKnucklesWeldInfo[1].BaseModel = *KNUCKLES_OBJECTS;
	NPCKnucklesWeldInfo[1].ModelA = KNUCKLES_OBJECTS[3];
	NPCKnucklesWeldInfo[1].ModelB = KNUCKLES_OBJECTS[4];
	NPCKnucklesWeldInfo[1].VertexPairCount = (uint8_t)(LengthOfArray(Knuckles_LowerArmIndices_DC) / 2);
	NPCKnucklesWeldInfo[1].WeldType = 2;
	NPCKnucklesWeldInfo[1].anonymous_5 = 0;
	NPCKnucklesWeldInfo[1].VertexBuffer = 0;
	NPCKnucklesWeldInfo[1].VertIndexes = Knuckles_LowerArmIndices_DC;
	NPCKnucklesWeldInfo[2].BaseModel = *KNUCKLES_OBJECTS;
	NPCKnucklesWeldInfo[2].ModelA = KNUCKLES_OBJECTS[6];
	v0 = KNUCKLES_OBJECTS[7];
	NPCKnucklesWeldInfo[2].VertIndexes = Knuckles_UpperArmIndices_DC;
	NPCKnucklesWeldInfo[2].ModelB = v0;
	NPCKnucklesWeldInfo[2].VertexPairCount = (uint8_t)(LengthOfArray(Knuckles_UpperArmIndices_DC) / 2);
	NPCKnucklesWeldInfo[2].WeldType = 2;
	NPCKnucklesWeldInfo[2].anonymous_5 = 0;
	NPCKnucklesWeldInfo[2].VertexBuffer = 0;
	NPCKnucklesWeldInfo[3].BaseModel = *KNUCKLES_OBJECTS;
	NPCKnucklesWeldInfo[3].ModelA = KNUCKLES_OBJECTS[7];
	NPCKnucklesWeldInfo[3].ModelB = KNUCKLES_OBJECTS[8];
	NPCKnucklesWeldInfo[3].VertexPairCount = (uint8_t)(LengthOfArray(Knuckles_LowerArmIndices_DC) / 2);
	NPCKnucklesWeldInfo[3].WeldType = 2;
	NPCKnucklesWeldInfo[3].anonymous_5 = 0;
	NPCKnucklesWeldInfo[3].VertexBuffer = 0;
	NPCKnucklesWeldInfo[3].VertIndexes = Knuckles_LowerArmIndices_DC;
	NPCKnucklesWeldInfo[4].BaseModel = *KNUCKLES_OBJECTS;
	NPCKnucklesWeldInfo[4].ModelA = KNUCKLES_OBJECTS[10];
	NPCKnucklesWeldInfo[4].ModelB = KNUCKLES_OBJECTS[11];
	NPCKnucklesWeldInfo[4].VertexPairCount = (uint8_t)(LengthOfArray(Knuckles_LegIndices_DC) / 2);
	NPCKnucklesWeldInfo[4].WeldType = 2;
	NPCKnucklesWeldInfo[4].anonymous_5 = 0;
	NPCKnucklesWeldInfo[4].VertexBuffer = 0;
	NPCKnucklesWeldInfo[4].VertIndexes = Knuckles_LegIndices_DC;
	NPCKnucklesWeldInfo[5].BaseModel = *KNUCKLES_OBJECTS;
	NPCKnucklesWeldInfo[5].ModelA = KNUCKLES_OBJECTS[11];
	NPCKnucklesWeldInfo[5].ModelB = KNUCKLES_OBJECTS[12];
	NPCKnucklesWeldInfo[5].VertexPairCount = (uint8_t)(LengthOfArray(Knuckles_LegIndices_DC) / 2);
	NPCKnucklesWeldInfo[5].WeldType = 2;
	NPCKnucklesWeldInfo[5].anonymous_5 = 0;
	NPCKnucklesWeldInfo[5].VertexBuffer = 0;
	NPCKnucklesWeldInfo[5].VertIndexes = Knuckles_LegIndices_DC;
	NPCKnucklesWeldInfo[6].BaseModel = *KNUCKLES_OBJECTS;
	NPCKnucklesWeldInfo[6].ModelA = KNUCKLES_OBJECTS[13];
	NPCKnucklesWeldInfo[6].ModelB = KNUCKLES_OBJECTS[14];
	NPCKnucklesWeldInfo[6].VertexPairCount = (uint8_t)(LengthOfArray(Knuckles_LegIndices_DC) / 2);
	NPCKnucklesWeldInfo[6].WeldType = 2;
	NPCKnucklesWeldInfo[6].anonymous_5 = 0;
	NPCKnucklesWeldInfo[6].VertexBuffer = 0;
	NPCKnucklesWeldInfo[6].VertIndexes = Knuckles_LegIndices_DC;
	NPCKnucklesWeldInfo[7].BaseModel = *KNUCKLES_OBJECTS;
	NPCKnucklesWeldInfo[7].ModelA = KNUCKLES_OBJECTS[14];
	NPCKnucklesWeldInfo[7].ModelB = KNUCKLES_OBJECTS[15];
	NPCKnucklesWeldInfo[7].VertexPairCount = (uint8_t)(LengthOfArray(Knuckles_LegIndices_DC) / 2);
	NPCKnucklesWeldInfo[7].WeldType = 2;
	NPCKnucklesWeldInfo[7].anonymous_5 = 0;
	NPCKnucklesWeldInfo[7].VertexBuffer = 0;
	NPCKnucklesWeldInfo[7].VertIndexes = Knuckles_LegIndices_DC;
	NPCKnucklesWeldInfo[8].BaseModel = *KNUCKLES_OBJECTS;
	NPCKnucklesWeldInfo[8].ModelA = KNUCKLES_OBJECTS[16];
	NPCKnucklesWeldInfo[8].ModelB = KNUCKLES_OBJECTS[17];
	NPCKnucklesWeldInfo[8].VertexPairCount = (uint8_t)(LengthOfArray(Knuckles_ShoeIndices_DC) / 2);
	NPCKnucklesWeldInfo[8].WeldType = 2;
	NPCKnucklesWeldInfo[8].anonymous_5 = 0;
	NPCKnucklesWeldInfo[8].VertexBuffer = 0;
	NPCKnucklesWeldInfo[8].VertIndexes = Knuckles_ShoeIndices_DC;
	NPCKnucklesWeldInfo[9].BaseModel = *KNUCKLES_OBJECTS;
	NPCKnucklesWeldInfo[9].ModelA = KNUCKLES_OBJECTS[18];
	v1 = KNUCKLES_OBJECTS[19];
	NPCKnucklesWeldInfo[9].VertIndexes = Knuckles_ShoeIndices_DC;
	NPCKnucklesWeldInfo[9].ModelB = v1;
	NPCKnucklesWeldInfo[9].VertexPairCount = (uint8_t)(LengthOfArray(Knuckles_ShoeIndices_DC) / 2);
	NPCKnucklesWeldInfo[9].WeldType = 2;
	NPCKnucklesWeldInfo[9].anonymous_5 = 0;
	NPCKnucklesWeldInfo[9].VertexBuffer = 0;
	NPCKnucklesWeldInfo[10].BaseModel = *KNUCKLES_OBJECTS;
	NPCKnucklesWeldInfo[10].ModelA = KNUCKLES_OBJECTS[20];
	NPCKnucklesWeldInfo[10].ModelB = KNUCKLES_OBJECTS[5];
	NPCKnucklesWeldInfo[10].VertexPairCount = (uint8_t)(LengthOfArray(Knuckles_HandIndices_DC) / 2);
	NPCKnucklesWeldInfo[10].WeldType = 2;
	NPCKnucklesWeldInfo[10].anonymous_5 = 0;
	NPCKnucklesWeldInfo[10].VertexBuffer = 0;
	NPCKnucklesWeldInfo[10].VertIndexes = Knuckles_HandIndices_DC;
	NPCKnucklesWeldInfo[11].BaseModel = *KNUCKLES_OBJECTS;
	NPCKnucklesWeldInfo[11].ModelA = KNUCKLES_OBJECTS[22];
	NPCKnucklesWeldInfo[11].ModelB = KNUCKLES_OBJECTS[9];
	NPCKnucklesWeldInfo[11].VertexPairCount = (uint8_t)(LengthOfArray(Knuckles_HandIndices_DC) / 2);
	NPCKnucklesWeldInfo[11].WeldType = 2;
	NPCKnucklesWeldInfo[11].anonymous_5 = 0;
	NPCKnucklesWeldInfo[11].VertexBuffer = 0;
	NPCKnucklesWeldInfo[11].VertIndexes = Knuckles_HandIndices_DC;
	NPCKnucklesWeldInfo[12].BaseModel = KNUCKLES_OBJECTS[1];
	NPCKnucklesWeldInfo[12].ModelA = KNUCKLES_OBJECTS[24];
	NPCKnucklesWeldInfo[12].ModelB = KNUCKLES_OBJECTS[25];
	NPCKnucklesWeldInfo[12].VertexPairCount = (uint8_t)(LengthOfArray(Knuckles_UpperArmIndices_DC) / 2);
	NPCKnucklesWeldInfo[12].WeldType = 2;
	NPCKnucklesWeldInfo[12].anonymous_5 = 0;
	NPCKnucklesWeldInfo[12].VertexBuffer = 0;
	NPCKnucklesWeldInfo[12].VertIndexes = Knuckles_UpperArmIndices_DC;
	NPCKnucklesWeldInfo[13].BaseModel = KNUCKLES_OBJECTS[1];
	NPCKnucklesWeldInfo[13].ModelA = KNUCKLES_OBJECTS[25];
	NPCKnucklesWeldInfo[13].ModelB = KNUCKLES_OBJECTS[26];
	NPCKnucklesWeldInfo[13].VertexPairCount = (uint8_t)(LengthOfArray(Knuckles_LowerArmIndices_DC) / 2);
	NPCKnucklesWeldInfo[13].WeldType = 2;
	NPCKnucklesWeldInfo[13].anonymous_5 = 0;
	NPCKnucklesWeldInfo[13].VertexBuffer = 0;
	NPCKnucklesWeldInfo[13].VertIndexes = Knuckles_LowerArmIndices_DC;
	NPCKnucklesWeldInfo[14].BaseModel = KNUCKLES_OBJECTS[1];
	NPCKnucklesWeldInfo[14].ModelA = KNUCKLES_OBJECTS[28];
	NPCKnucklesWeldInfo[14].ModelB = KNUCKLES_OBJECTS[29];
	NPCKnucklesWeldInfo[14].VertexPairCount = (uint8_t)(LengthOfArray(Knuckles_UpperArmIndices_DC) / 2);
	NPCKnucklesWeldInfo[14].WeldType = 2;
	NPCKnucklesWeldInfo[14].anonymous_5 = 0;
	NPCKnucklesWeldInfo[14].VertexBuffer = 0;
	NPCKnucklesWeldInfo[14].VertIndexes = Knuckles_UpperArmIndices_DC;
	NPCKnucklesWeldInfo[15].BaseModel = KNUCKLES_OBJECTS[1];
	NPCKnucklesWeldInfo[15].ModelA = KNUCKLES_OBJECTS[29];
	NPCKnucklesWeldInfo[15].ModelB = KNUCKLES_OBJECTS[30];
	NPCKnucklesWeldInfo[15].VertexPairCount = (uint8_t)(LengthOfArray(Knuckles_LowerArmIndices_DC) / 2);
	NPCKnucklesWeldInfo[15].WeldType = 2;
	NPCKnucklesWeldInfo[15].anonymous_5 = 0;
	NPCKnucklesWeldInfo[15].VertexBuffer = 0;
	NPCKnucklesWeldInfo[15].VertIndexes = Knuckles_LowerArmIndices_DC;
	NPCKnucklesWeldInfo[16].BaseModel = KNUCKLES_OBJECTS[1];
	NPCKnucklesWeldInfo[16].ModelA = KNUCKLES_OBJECTS[32];
	NPCKnucklesWeldInfo[16].ModelB = KNUCKLES_OBJECTS[33];
	NPCKnucklesWeldInfo[16].VertexPairCount = (uint8_t)(LengthOfArray(Knuckles_LegIndices_DC) / 2);
	NPCKnucklesWeldInfo[16].WeldType = 2;
	NPCKnucklesWeldInfo[16].anonymous_5 = 0;
	NPCKnucklesWeldInfo[16].VertexBuffer = 0;
	NPCKnucklesWeldInfo[16].VertIndexes = Knuckles_LegIndices_DC;
	NPCKnucklesWeldInfo[17].BaseModel = KNUCKLES_OBJECTS[1];
	NPCKnucklesWeldInfo[17].ModelA = KNUCKLES_OBJECTS[33];
	NPCKnucklesWeldInfo[17].ModelB = KNUCKLES_OBJECTS[34];
	NPCKnucklesWeldInfo[17].VertexPairCount = (uint8_t)(LengthOfArray(Knuckles_LegIndices_DC) / 2);
	NPCKnucklesWeldInfo[17].WeldType = 2;
	NPCKnucklesWeldInfo[17].anonymous_5 = 0;
	NPCKnucklesWeldInfo[17].VertexBuffer = 0;
	NPCKnucklesWeldInfo[17].VertIndexes = Knuckles_LegIndices_DC;
	NPCKnucklesWeldInfo[18].BaseModel = KNUCKLES_OBJECTS[1];
	NPCKnucklesWeldInfo[18].ModelA = KNUCKLES_OBJECTS[35];
	NPCKnucklesWeldInfo[18].ModelB = KNUCKLES_OBJECTS[36];
	NPCKnucklesWeldInfo[18].VertexPairCount = (uint8_t)(LengthOfArray(Knuckles_LegIndices_DC) / 2);
	NPCKnucklesWeldInfo[18].WeldType = 2;
	NPCKnucklesWeldInfo[18].anonymous_5 = 0;
	NPCKnucklesWeldInfo[18].VertexBuffer = 0;
	NPCKnucklesWeldInfo[18].VertIndexes = Knuckles_LegIndices_DC;
	NPCKnucklesWeldInfo[19].BaseModel = KNUCKLES_OBJECTS[1];
	NPCKnucklesWeldInfo[19].ModelA = KNUCKLES_OBJECTS[36];
	v2 = KNUCKLES_OBJECTS[37];
	NPCKnucklesWeldInfo[19].anonymous_5 = 0;
	NPCKnucklesWeldInfo[19].VertexBuffer = 0;
	NPCKnucklesWeldInfo[19].VertIndexes = Knuckles_LegIndices_DC;
	NPCKnucklesWeldInfo[19].ModelB = v2;
	NPCKnucklesWeldInfo[19].VertexPairCount = (uint8_t)(LengthOfArray(Knuckles_LegIndices_DC) / 2);
	NPCKnucklesWeldInfo[19].WeldType = 2;
	NPCKnucklesWeldInfo[20].BaseModel = KNUCKLES_OBJECTS[1];
	NPCKnucklesWeldInfo[20].ModelA = KNUCKLES_OBJECTS[38];
	NPCKnucklesWeldInfo[20].ModelB = KNUCKLES_OBJECTS[39];
	NPCKnucklesWeldInfo[20].anonymous_5 = 0;
	NPCKnucklesWeldInfo[20].VertexBuffer = 0;
	NPCKnucklesWeldInfo[20].VertexPairCount = (uint8_t)(LengthOfArray(Knuckles_ShoeIndices_DC) / 2);
	NPCKnucklesWeldInfo[20].WeldType = 2;
	NPCKnucklesWeldInfo[20].VertIndexes = Knuckles_ShoeIndices_DC;
	NPCKnucklesWeldInfo[21].BaseModel = KNUCKLES_OBJECTS[1];
	NPCKnucklesWeldInfo[21].ModelA = KNUCKLES_OBJECTS[40];
	v3 = KNUCKLES_OBJECTS[41];
	NPCKnucklesWeldInfo[21].anonymous_5 = 0;
	NPCKnucklesWeldInfo[21].VertexBuffer = 0;
	NPCKnucklesWeldInfo[21].ModelB = v3;
	NPCKnucklesWeldInfo[21].VertIndexes = Knuckles_ShoeIndices_DC;
	NPCKnucklesWeldInfo[21].VertexPairCount = (uint8_t)(LengthOfArray(Knuckles_ShoeIndices_DC) / 2);
	NPCKnucklesWeldInfo[21].WeldType = 2;
	NPCKnucklesWeldInfo[22].BaseModel = KNUCKLES_OBJECTS[1];
	NPCKnucklesWeldInfo[22].ModelA = KNUCKLES_OBJECTS[42];
	v4 = KNUCKLES_OBJECTS[27];
	NPCKnucklesWeldInfo[22].anonymous_5 = 0;
	NPCKnucklesWeldInfo[22].VertexBuffer = 0;
	NPCKnucklesWeldInfo[22].ModelB = v4;
	NPCKnucklesWeldInfo[22].VertIndexes = Knuckles_HandIndices_DC;
	NPCKnucklesWeldInfo[22].VertexPairCount = (uint8_t)(LengthOfArray(Knuckles_HandIndices_DC) / 2);
	NPCKnucklesWeldInfo[22].WeldType = 2;
	NPCKnucklesWeldInfo[23].BaseModel = KNUCKLES_OBJECTS[1];
	NPCKnucklesWeldInfo[23].ModelA = KNUCKLES_OBJECTS[44];
	v5 = KNUCKLES_OBJECTS[31];
	NPCKnucklesWeldInfo[23].anonymous_5 = 0;
	NPCKnucklesWeldInfo[23].VertexBuffer = 0;
	NPCKnucklesWeldInfo[24].BaseModel = 0;
	NPCKnucklesWeldInfo[24].ModelA = 0;
	NPCKnucklesWeldInfo[23].VertIndexes = Knuckles_HandIndices_DC;
	NPCKnucklesWeldInfo[24].ModelB = 0;
	NPCKnucklesWeldInfo[24].VertexPairCount = 0;
	NPCKnucklesWeldInfo[24].VertexBuffer = 0;
	NPCKnucklesWeldInfo[23].ModelB = v5;
	NPCKnucklesWeldInfo[23].VertexPairCount = (uint8_t)(LengthOfArray(Knuckles_HandIndices_DC) / 2);
	NPCKnucklesWeldInfo[23].WeldType = 2;
	NPCKnucklesWeldInfo[24].VertIndexes = 0;
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
	AmyWeldInfo[0].VertexPairCount = (uint8_t)(LengthOfArray(Amy_UpperArmIndices_DC) / 2);
	AmyWeldInfo[0].WeldType = 2;
	AmyWeldInfo[0].VertIndexes = Amy_UpperArmIndices_DC;
	AmyWeldInfo[1].BaseModel = *AMY_OBJECTS;
	AmyWeldInfo[1].ModelA = AMY_OBJECTS[7];
	AmyWeldInfo[1].ModelB = AMY_OBJECTS[8];
	AmyWeldInfo[1].VertexPairCount = (uint8_t)(LengthOfArray(Amy_LowerArmIndices_DC) / 2);
	AmyWeldInfo[1].WeldType = 2;
	AmyWeldInfo[1].anonymous_5 = 0;
	AmyWeldInfo[1].VertexBuffer = 0;
	AmyWeldInfo[1].VertIndexes = Amy_LowerArmIndices_DC;
	AmyWeldInfo[2].BaseModel = *AMY_OBJECTS;
	AmyWeldInfo[2].ModelA = AMY_OBJECTS[9];
	AmyWeldInfo[2].ModelB = AMY_OBJECTS[10];
	AmyWeldInfo[2].VertexPairCount = (uint8_t)(LengthOfArray(Amy_UpperArmIndices_DC) / 2);
	AmyWeldInfo[2].WeldType = 2;
	AmyWeldInfo[2].anonymous_5 = 0;
	AmyWeldInfo[2].VertexBuffer = 0;
	AmyWeldInfo[2].VertIndexes = Amy_UpperArmIndices_DC;
	AmyWeldInfo[3].BaseModel = *AMY_OBJECTS;
	AmyWeldInfo[3].ModelA = AMY_OBJECTS[10];
	v0 = AMY_OBJECTS[11];
	AmyWeldInfo[3].VertIndexes = Amy_LowerArmIndices_DC;
	AmyWeldInfo[3].ModelB = v0;
	AmyWeldInfo[3].VertexPairCount = (uint8_t)(LengthOfArray(Amy_LowerArmIndices_DC) / 2);
	AmyWeldInfo[3].WeldType = 2;
	AmyWeldInfo[3].anonymous_5 = 0;
	AmyWeldInfo[3].VertexBuffer = 0;
	AmyWeldInfo[4].BaseModel = *AMY_OBJECTS;
	AmyWeldInfo[4].ModelA = AMY_OBJECTS[12];
	AmyWeldInfo[4].ModelB = AMY_OBJECTS[13];
	AmyWeldInfo[4].VertexPairCount = (uint8_t)(LengthOfArray(Amy_LegIndices_DC) / 2);
	AmyWeldInfo[4].WeldType = 2;
	AmyWeldInfo[4].anonymous_5 = 0;
	AmyWeldInfo[4].VertexBuffer = 0;
	AmyWeldInfo[4].VertIndexes = Amy_LegIndices_DC;
	AmyWeldInfo[5].BaseModel = *AMY_OBJECTS;
	AmyWeldInfo[5].ModelA = AMY_OBJECTS[13];
	AmyWeldInfo[5].ModelB = AMY_OBJECTS[14];
	AmyWeldInfo[5].VertexPairCount = (uint8_t)(LengthOfArray(Amy_LegIndices_DC) / 2);
	AmyWeldInfo[5].WeldType = 2;
	AmyWeldInfo[5].anonymous_5 = 0;
	AmyWeldInfo[5].VertIndexes = Amy_LegIndices_DC;
	AmyWeldInfo[5].VertexBuffer = 0;
	AmyWeldInfo[6].BaseModel = *AMY_OBJECTS;
	AmyWeldInfo[6].ModelA = AMY_OBJECTS[15];
	v1 = AMY_OBJECTS[16];
	AmyWeldInfo[6].VertIndexes = Amy_LegIndices_DC;
	AmyWeldInfo[6].ModelB = v1;
	AmyWeldInfo[6].VertexPairCount = (uint8_t)(LengthOfArray(Amy_LegIndices_DC) / 2);
	AmyWeldInfo[6].WeldType = 2;
	AmyWeldInfo[6].anonymous_5 = 0;
	AmyWeldInfo[6].VertexBuffer = 0;
	AmyWeldInfo[7].BaseModel = *AMY_OBJECTS;
	AmyWeldInfo[7].ModelA = AMY_OBJECTS[16];
	v2 = AMY_OBJECTS[17];
	AmyWeldInfo[7].VertIndexes = Amy_LegIndices_DC;
	AmyWeldInfo[7].ModelB = v2;
	AmyWeldInfo[7].VertexPairCount = (uint8_t)(LengthOfArray(Amy_LegIndices_DC) / 2);
	AmyWeldInfo[7].WeldType = 2;
	AmyWeldInfo[7].anonymous_5 = 0;
	AmyWeldInfo[7].VertexBuffer = 0;
	AmyWeldInfo[8].BaseModel = *AMY_OBJECTS;
	AmyWeldInfo[8].ModelA = AMY_OBJECTS[18];
	AmyWeldInfo[8].ModelB = AMY_OBJECTS[19];
	AmyWeldInfo[8].VertexPairCount = (uint8_t)(LengthOfArray(Amy_ShoeIndices_DC) / 2);
	AmyWeldInfo[8].WeldType = 2;
	AmyWeldInfo[8].anonymous_5 = 0;
	AmyWeldInfo[8].VertexBuffer = 0;
	AmyWeldInfo[8].VertIndexes = Amy_ShoeIndices_DC;
	AmyWeldInfo[9].BaseModel = *AMY_OBJECTS;
	AmyWeldInfo[9].ModelA = AMY_OBJECTS[20];
	v3 = AMY_OBJECTS[21];
	AmyWeldInfo[9].VertIndexes = Amy_ShoeIndices_DC;
	AmyWeldInfo[9].ModelB = v3;
	AmyWeldInfo[9].VertexPairCount = (uint8_t)(LengthOfArray(Amy_ShoeIndices_DC) / 2);
	AmyWeldInfo[9].WeldType = 2;
	AmyWeldInfo[9].anonymous_5 = 0;
	AmyWeldInfo[9].VertexBuffer = 0;
	AmyWeldInfo[10].BaseModel = *AMY_OBJECTS;
	AmyWeldInfo[10].ModelA = AMY_OBJECTS[22];
	AmyWeldInfo[10].ModelB = AMY_OBJECTS[23];
	AmyWeldInfo[10].VertexPairCount = (uint8_t)(LengthOfArray(Amy_HandIndices_DC) / 2);
	AmyWeldInfo[10].WeldType = 2;
	AmyWeldInfo[10].anonymous_5 = 0;
	AmyWeldInfo[10].VertexBuffer = 0;
	AmyWeldInfo[10].VertIndexes = Amy_HandIndices_DC;
	AmyWeldInfo[11].BaseModel = *AMY_OBJECTS;
	AmyWeldInfo[11].ModelA = AMY_OBJECTS[24];
	AmyWeldInfo[11].ModelB = AMY_OBJECTS[25];
	AmyWeldInfo[11].VertexPairCount = (uint8_t)(LengthOfArray(Amy_HandIndices_DC) / 2);
	AmyWeldInfo[11].WeldType = 2;
	AmyWeldInfo[11].anonymous_5 = 0;
	AmyWeldInfo[11].VertexBuffer = 0;
	AmyWeldInfo[11].VertIndexes = Amy_HandIndices_DC;
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
	NPCAmyWeldInfo[0].VertexPairCount = (uint8_t)(LengthOfArray(Amy_UpperArmIndices_DC) / 2);
	NPCAmyWeldInfo[0].WeldType = 2;
	NPCAmyWeldInfo[0].VertIndexes = Amy_UpperArmIndices_DC;
	NPCAmyWeldInfo[1].BaseModel = *AMY_OBJECTS;
	NPCAmyWeldInfo[1].ModelA = AMY_OBJECTS[7];
	NPCAmyWeldInfo[1].ModelB = AMY_OBJECTS[8];
	NPCAmyWeldInfo[1].VertexPairCount = (uint8_t)(LengthOfArray(Amy_LowerArmIndices_DC) / 2);
	NPCAmyWeldInfo[1].WeldType = 2;
	NPCAmyWeldInfo[1].anonymous_5 = 0;
	NPCAmyWeldInfo[1].VertexBuffer = 0;
	NPCAmyWeldInfo[1].VertIndexes = Amy_LowerArmIndices_DC;
	NPCAmyWeldInfo[2].BaseModel = *AMY_OBJECTS;
	NPCAmyWeldInfo[2].ModelA = AMY_OBJECTS[9];
	NPCAmyWeldInfo[2].ModelB = AMY_OBJECTS[10];
	NPCAmyWeldInfo[2].VertexPairCount = (uint8_t)(LengthOfArray(Amy_UpperArmIndices_DC) / 2);
	NPCAmyWeldInfo[2].WeldType = 2;
	NPCAmyWeldInfo[2].anonymous_5 = 0;
	NPCAmyWeldInfo[2].VertexBuffer = 0;
	NPCAmyWeldInfo[2].VertIndexes = Amy_UpperArmIndices_DC;
	NPCAmyWeldInfo[3].BaseModel = *AMY_OBJECTS;
	NPCAmyWeldInfo[3].ModelA = AMY_OBJECTS[10];
	v0 = AMY_OBJECTS[11];
	NPCAmyWeldInfo[3].VertIndexes = Amy_LowerArmIndices_DC;
	NPCAmyWeldInfo[3].ModelB = v0;
	NPCAmyWeldInfo[3].VertexPairCount = (uint8_t)(LengthOfArray(Amy_LowerArmIndices_DC) / 2);
	NPCAmyWeldInfo[3].WeldType = 2;
	NPCAmyWeldInfo[3].anonymous_5 = 0;
	NPCAmyWeldInfo[3].VertexBuffer = 0;
	NPCAmyWeldInfo[4].BaseModel = *AMY_OBJECTS;
	NPCAmyWeldInfo[4].ModelA = AMY_OBJECTS[12];
	NPCAmyWeldInfo[4].ModelB = AMY_OBJECTS[13];
	NPCAmyWeldInfo[4].VertexPairCount = (uint8_t)(LengthOfArray(Amy_LegIndices_DC) / 2);
	NPCAmyWeldInfo[4].WeldType = 2;
	NPCAmyWeldInfo[4].anonymous_5 = 0;
	NPCAmyWeldInfo[4].VertexBuffer = 0;
	NPCAmyWeldInfo[4].VertIndexes = Amy_LegIndices_DC;
	NPCAmyWeldInfo[5].BaseModel = *AMY_OBJECTS;
	NPCAmyWeldInfo[5].ModelA = AMY_OBJECTS[13];
	NPCAmyWeldInfo[5].ModelB = AMY_OBJECTS[14];
	NPCAmyWeldInfo[5].VertexPairCount = (uint8_t)(LengthOfArray(Amy_LegIndices_DC) / 2);
	NPCAmyWeldInfo[5].WeldType = 2;
	NPCAmyWeldInfo[5].anonymous_5 = 0;
	NPCAmyWeldInfo[5].VertexBuffer = 0;
	NPCAmyWeldInfo[5].VertIndexes = Amy_LegIndices_DC;
	NPCAmyWeldInfo[6].BaseModel = *AMY_OBJECTS;
	NPCAmyWeldInfo[6].ModelA = AMY_OBJECTS[15];
	v1 = AMY_OBJECTS[16];
	NPCAmyWeldInfo[6].VertexPairCount = (uint8_t)(LengthOfArray(Amy_LegIndices_DC) / 2);
	NPCAmyWeldInfo[6].anonymous_5 = 0;
	NPCAmyWeldInfo[6].VertexBuffer = 0;
	NPCAmyWeldInfo[6].VertIndexes = Amy_LegIndices_DC;
	NPCAmyWeldInfo[6].ModelB = v1;
	NPCAmyWeldInfo[6].WeldType = 2;
	NPCAmyWeldInfo[7].BaseModel = *AMY_OBJECTS;
	NPCAmyWeldInfo[7].ModelA = AMY_OBJECTS[16];
	v2 = AMY_OBJECTS[17];
	NPCAmyWeldInfo[7].VertexPairCount = (uint8_t)(LengthOfArray(Amy_LegIndices_DC) / 2);
	NPCAmyWeldInfo[7].anonymous_5 = 0;
	NPCAmyWeldInfo[7].VertexBuffer = 0;
	NPCAmyWeldInfo[7].VertIndexes = Amy_LegIndices_DC;
	NPCAmyWeldInfo[7].ModelB = v2;
	NPCAmyWeldInfo[7].WeldType = 2;
	NPCAmyWeldInfo[8].BaseModel = *AMY_OBJECTS;
	NPCAmyWeldInfo[8].ModelA = AMY_OBJECTS[18];
	NPCAmyWeldInfo[8].ModelB = AMY_OBJECTS[19];
	NPCAmyWeldInfo[8].anonymous_5 = 0;
	NPCAmyWeldInfo[8].VertexBuffer = 0;
	NPCAmyWeldInfo[8].WeldType = 2;
	NPCAmyWeldInfo[8].VertexPairCount = (uint8_t)(LengthOfArray(Amy_ShoeIndices_DC) / 2);
	NPCAmyWeldInfo[8].VertIndexes = Amy_ShoeIndices_DC;
	NPCAmyWeldInfo[9].BaseModel = *AMY_OBJECTS;
	NPCAmyWeldInfo[9].ModelA = AMY_OBJECTS[20];
	v3 = AMY_OBJECTS[21];
	NPCAmyWeldInfo[9].anonymous_5 = 0;
	NPCAmyWeldInfo[9].VertexBuffer = 0;
	NPCAmyWeldInfo[9].VertexPairCount = (uint8_t)(LengthOfArray(Amy_ShoeIndices_DC) / 2);
	NPCAmyWeldInfo[9].VertIndexes = Amy_ShoeIndices_DC;
	NPCAmyWeldInfo[9].ModelB = v3;
	NPCAmyWeldInfo[9].WeldType = 2;
	NPCAmyWeldInfo[10].BaseModel = *AMY_OBJECTS;
	NPCAmyWeldInfo[10].ModelA = AMY_OBJECTS[22];
	NPCAmyWeldInfo[10].ModelB = AMY_OBJECTS[23];
	NPCAmyWeldInfo[10].anonymous_5 = 0;
	NPCAmyWeldInfo[10].VertexBuffer = 0;
	NPCAmyWeldInfo[10].VertexPairCount = (uint8_t)(LengthOfArray(Amy_HandIndices_DC) / 2);
	NPCAmyWeldInfo[10].WeldType = 2;
	NPCAmyWeldInfo[10].VertIndexes = Amy_HandIndices_DC;
	NPCAmyWeldInfo[11].BaseModel = *AMY_OBJECTS;
	NPCAmyWeldInfo[11].ModelA = AMY_OBJECTS[24];
	v4 = AMY_OBJECTS[25];
	NPCAmyWeldInfo[11].anonymous_5 = 0;
	NPCAmyWeldInfo[11].VertexBuffer = 0;
	NPCAmyWeldInfo[12].BaseModel = 0;
	NPCAmyWeldInfo[12].ModelA = 0;
	NPCAmyWeldInfo[11].ModelB = v4;
	NPCAmyWeldInfo[11].VertexPairCount = (uint8_t)(LengthOfArray(Amy_HandIndices_DC) / 2);
	NPCAmyWeldInfo[11].WeldType = 2;
	NPCAmyWeldInfo[11].VertIndexes = Amy_HandIndices_DC;
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

void __cdecl InitMetalSonicWeldInfo_Fix()
{
	NJS_OBJECT *v0; // esi@1

	MetalSonicWeldInfo[0].BaseModel = *SONIC_OBJECTS;
	MetalSonicWeldInfo[0].ModelA = SONIC_OBJECTS[5];
	MetalSonicWeldInfo[0].ModelB = 0;
	MetalSonicWeldInfo[0].WeldType = 4;
	MetalSonicWeldInfo[0].anonymous_5 = 0;
	MetalSonicWeldInfo[0].VertexBuffer = 0;
	MetalSonicWeldInfo[0].VertIndexes = 0;
	MetalSonicWeldInfo[0].VertexPairCount = 2;
	MetalSonicWeldInfo[1].BaseModel = *SONIC_OBJECTS;
	v0 = SONIC_OBJECTS[11];
	MetalSonicWeldInfo[1].VertexPairCount = 2;
	MetalSonicWeldInfo[1].ModelA = v0;
	MetalSonicWeldInfo[1].ModelB = 0;
	MetalSonicWeldInfo[1].WeldType = 5;
	MetalSonicWeldInfo[1].anonymous_5 = 0;
	MetalSonicWeldInfo[1].VertexBuffer = 0;
	MetalSonicWeldInfo[1].VertIndexes = 0;
	MetalSonicWeldInfo[2].BaseModel = *SONIC_OBJECTS;
	MetalSonicWeldInfo[2].ModelA = SONIC_OBJECTS[59];
	MetalSonicWeldInfo[2].ModelB = 0;
	MetalSonicWeldInfo[2].VertexPairCount = 0;
	MetalSonicWeldInfo[2].WeldType = 7;
	MetalSonicWeldInfo[2].anonymous_5 = 0;
	MetalSonicWeldInfo[2].VertexBuffer = 0;
	MetalSonicWeldInfo[2].VertIndexes = 0;
	MetalSonicWeldInfo[3].BaseModel = *SONIC_OBJECTS;
	MetalSonicWeldInfo[3].ModelA = SONIC_OBJECTS[61];
	MetalSonicWeldInfo[3].ModelB = 0;
	MetalSonicWeldInfo[3].VertexPairCount = 0;
	MetalSonicWeldInfo[3].anonymous_5 = 0;
	MetalSonicWeldInfo[3].VertexBuffer = 0;
	MetalSonicWeldInfo[3].VertIndexes = 0;
	MetalSonicWeldInfo[3].WeldType = 6;
	MetalSonicWeldInfo[4].BaseModel = *SONIC_OBJECTS;
	MetalSonicWeldInfo[4].ModelA = SONIC_OBJECTS[16];
	MetalSonicWeldInfo[4].ModelB = 0;
	MetalSonicWeldInfo[4].VertexPairCount = 0;
	MetalSonicWeldInfo[4].WeldType = 6;
	MetalSonicWeldInfo[4].anonymous_5 = 0;
	MetalSonicWeldInfo[4].VertexBuffer = 0;
	MetalSonicWeldInfo[4].VertIndexes = 0;
	MetalSonicWeldInfo[5].BaseModel = *SONIC_OBJECTS;
	MetalSonicWeldInfo[5].ModelA = SONIC_OBJECTS[21];
	MetalSonicWeldInfo[5].ModelB = 0;
	MetalSonicWeldInfo[5].VertexPairCount = 0;
	MetalSonicWeldInfo[5].WeldType = 7;
	MetalSonicWeldInfo[5].anonymous_5 = 0;
	MetalSonicWeldInfo[5].VertexBuffer = 0;
	MetalSonicWeldInfo[5].VertIndexes = 0;
	MetalSonicWeldInfo[6].BaseModel = *SONIC_OBJECTS;
	MetalSonicWeldInfo[6].ModelA = SONIC_OBJECTS[45];
	MetalSonicWeldInfo[6].ModelB = 0;
	MetalSonicWeldInfo[6].VertexPairCount = 0;
	MetalSonicWeldInfo[6].WeldType = 8;
	MetalSonicWeldInfo[6].anonymous_5 = 0;
	MetalSonicWeldInfo[6].VertexBuffer = 0;
	MetalSonicWeldInfo[7].ModelA = 0;
	MetalSonicWeldInfo[7].ModelB = 0;
	MetalSonicWeldInfo[7].VertexPairCount = 0;
	MetalSonicWeldInfo[7].VertexBuffer = 0;
	MetalSonicWeldInfo[6].VertIndexes = 0;
	MetalSonicWeldInfo[7].BaseModel = 0;
	MetalSonicWeldInfo[7].VertIndexes = 0;
}

void __cdecl Sonic_Run1Ani_mod(CharObj2 *a1)
{
	ObjectMaster *v1; // eax@3

	if (MetalSonicFlag)
	{
		if (a1->AnimationThing.Index != 12)
		{
			v1 = LoadObject(LoadObj_Data1, 3, MetalSonic_AfterImages_Main);
			if (v1)
			{
				v1->Data1->Object = (NJS_OBJECT*)5;
			}
		}
		a1->AnimationThing.Index = 12;
	}
	else
	{
		a1->AnimationThing.Index = 12;
	}
}

static void __declspec(naked) Sonic_Run1Ani_swap()
{
	__asm
	{
		push esi // a1

		// Call your __cdecl function here:
		call Sonic_Run1Ani_mod

		pop esi // a1
		retn
	}
}

void __cdecl Sonic_Run2Ani_mod(CharObj2 *a1)
{
	ObjectMaster *v1; // eax@3

	if (MetalSonicFlag)
	{
		if (a1->AnimationThing.Index != 146)
		{
			v1 = LoadObject(LoadObj_Data1, 3, MetalSonic_AfterImages_Main);
			if (v1)
			{
				v1->Data1->Object = (NJS_OBJECT*)10;
			}
		}
		a1->AnimationThing.Index = 146;
	}
	else
	{
		a1->AnimationThing.Index = 13;
	}
}

static void __declspec(naked) Sonic_Run2Ani_swap()
{
	__asm
	{
		push esi // a1

		// Call your __cdecl function here:
		call Sonic_Run2Ani_mod

		pop esi // a1
		retn
	}
}

void __cdecl Sonic_Run1Ani_orig(CharObj2 *a1)
{
	ObjectMaster *v1; // eax@3

	if (MetalSonicFlag)
	{
		if (a1->AnimationThing.Index != 146)
		{
			v1 = LoadObject(LoadObj_Data1, 3, MetalSonic_AfterImages_Main);
			if (v1)
			{
				v1->Data1->Object = (NJS_OBJECT*)5;
			}
		}
		a1->AnimationThing.Index = 146;
	}
	else
	{
		a1->AnimationThing.Index = 12;
	}
}

static void __declspec(naked) Sonic_Run1Ani_origasm()
{
	__asm
	{
		push esi // a1

		// Call your __cdecl function here:
		call Sonic_Run1Ani_orig

		pop esi // a1
		retn
	}
}

//Lantern API Fixes
NJS_MATERIAL* Specular0[] = {

	//Birdie Material Fixes
	&material_8D4CAF2CC2D2CC7B1B5[0],
	&material_8D4CAF2CC2D2CC7B1B5[1],
	&material_8D4CAF2CC2D2CC7B1B5[2],
	&material_8D4CAF2CC2D2CC7B1B5[3],
	&material_8D4CAF2CC2D2CC7B1B5[4],
	&material_8D4CAF2D05C4026A461[0],
	&material_8D4CAF2CE87C76A3764[0],
	&material_8D4CAF2E1113A8693BD[0],
	&material_8D4CAF2E1113A8693BD[1],
	&material_8D4CAF2E1113A8693BD[2],
	&material_8D4CAF2E1113A8693BD[3],
	&material_8D4CAF2E1113A8693BD[4],
	&material_8D4CAF2D47978F26D49[0],
	&material_8D4CAF2D65D34274B2D[0],
	&material_8D4CAF2D8C00C49DCD9[0],
	&material_8D4CAF2DCEC878E36AD[0],
	&material_8D4CAF2DF0647AE1D44[0],

	//Tornado Destroyed
	&matlist_0251D088[30],
	&matlist_02518540[2],

	//Tornado 2 (EV Sky Chase)
	&material_8D4E896FEA3542F8997[2],
	&material_8D4E896FEA3542F8997[3],
	&material_8D4E89C4BBB70AD861C[3],

	//Tornado 2 (Saturn Sky Chase)
	&matlist_000E58D0[2],
	&matlist_000E3994[2],
	&matlist_000E3994[3],

	//Tornado 2 Transformation
	&matlist_024535B8[2],
	&matlist_024535B8[4],
	&matlist_0244A340[4],
};

NJS_MATERIAL* Specular1[] = {

	//Tails Jet Anklet
	&matlist_001B197C[0],
	&matlist_001B197C[1],
	&matlist_001B197C[2],
	&matlist_001B197C[3],
	&matlist_001B197C[4],
	&matlist_001B1474[0],
	&matlist_001B1474[1],
	&matlist_001B1474[2],
	&matlist_001B1474[3],
	&matlist_001B1474[4],

	//Sky Chase
	//EV Tornado 1
	&matlist_024ADD58[1],
	&matlist_024ADD58[15],
	&matlist_024ADD58[22],
	&matlist_024AD118[0],
	&matlist_024AD118[1],

	//Tornado 2 (Saturn Sky Chase)
	&matlist_000E0A5C[0],
	&matlist_000E0A5C[1],

	//Tornado 2 Changed (Event)
	&material_8D4714ACE7FAE0BE986[0],
	&material_8D4714ACE7FAE0BE986[1],
};

NJS_MATERIAL* Specular2[] = {
	//Sonic Material Fixes
	&material_8D45386FE2A37524DDB[0],
	&material_8D45386FE2A37524DDB[1],
	&material_8D45386FE2A37524DDB[2],
	&material_8D45386FE2A37524DDB[3],
	&material_8D45386FE2A37524DDB[4],
	&material_8D4538706DFFCF0F5E6[0],
	&material_8D453744DFBDA704FB5[0],
	&material_8D453744DFBDA704FB5[1],
	&material_8D453744DFBDA704FB5[2],
	&material_8D453744DFBDA704FB5[3],
	&material_8D453744DFBDA704FB5[4],
	&material_8D453744F8AE4B8D0AD[0],
	&material_8D453744F8AE4B8D0AD[1],
	&material_8D453744F8AE4B8D0AD[2],
	&material_8D45374EFDCAB6B4D4F[0],
	&material_8D45374EFDCAB6B4D4F[1],
	&material_8D45374EFDCAB6B4D4F[2],
	&material_8D45374EFDCAB6B4D4F[3],
	&material_8D45374EFDCAB6B4D4F[4],
	&material_8D45374F130F5C79FF7[0],
	&material_8D45374F130F5C79FF7[1],
	&material_8D45374F130F5C79FF7[2],
	&material_8D4580D5179AF3054F4[0],
	&material_8D4580D5179AF3054F4[1],
	&material_8D4580D5179AF3054F4[2],
	&material_8D4580D5179AF3054F4[3],
	&material_8D4580D54DD3234F8AA[3],
	&material_8D4580D54DD3234F8AA[4],
	&material_8D4580D54DD3234F8AA[5],
	&material_8D45387725BB21BF7C9[0],
	&material_8D45387725BB21BF7C9[1],
	&material_8D45387725BB21BF7C9[2],
	&material_8D45387725BB21BF7C9[3],
	&material_8D45387725BB21BF7C9[4],
	&material_8D4538948C5CFF76174[1],
	&material_8D4536C0BCBD3B5E700[0],
	&material_8D4536C0BCBD3B5E700[1],
	&material_8D4536C0BCBD3B5E700[2],
	&material_8D4536C0BCBD3B5E700[3],
	&material_8D4536C0E90CA767828[0],
	&material_8D4536C0E90CA767828[1],
	&material_8D4536BFD8E4B341B74[0],
	&material_8D4536BFD8E4B341B74[1],
	&material_8D4536BFD8E4B341B74[2],
	&material_8D4536BFD8E4B341B74[3],
	&material_8D4536C0D1E494A5641[0],
	&material_8D4536C0D1E494A5641[1],
	&material_8D445DBA48B46544BCC[0],
	&material_8D445DBA1E34DE0325F[0],
	&material_8D445DEFEB3C0F9D274[0],
	&material_8D445DEFEB3C0F9D274[1],
	&material_8D445DF7F10AC32787C[0],
	&material_8D453870D73094ABB3E[0],
	&material_8D445E8EE925057D39E[0],
	&material_8D445E9542EB249ABDE[0],
	&material_8D445E9542EB249ABDE[1],
	&material_8D445E9542EB249ABDE[2],
	&material_8D45DC7A3D32ECBD48B[0],
	&material_8D45DC7A3D32ECBD48B[1],
	&material_8D45DC7A6D7EE9CC1AF[0],
	&material_8D45DC7A6D7EE9CC1AF[1],
	&material_8D45DC7B286D367256C[0],
	&material_8D445E8F38F3E091FE6[0],
	&material_8D445E8F58E22C460E5[0],
	&material_8D445E956B2F598F7BA[0],
	&material_8D445E956B2F598F7BA[1],
	&material_8D445E956B2F598F7BA[2],
	&material_8D45DC7BB5A04CB7D68[0],
	&material_8D45DC7BB5A04CB7D68[1],
	&material_8D45DC7C428C94FBC56[0],
	&material_8D45DC7C428C94FBC56[1],
	&material_8D45DC7CF67FAB8C487[0],
	&material_8D445E8FA1B36037376[0],
	&material_8D445E8FC5A0ADECF0B[0],
	&material_8D445E95BE65D66A1A7[0],
	&material_8D445E95BE65D66A1A7[1],
	&material_8D445E95BE65D66A1A7[2],
	&material_8D445E8FE7181050EBC[0],
	&material_8D445E90038DA3030F6[0],
	&material_8D445E95E551C95391C[0],
	&material_8D445E95E551C95391C[1],
	&material_8D445E95E551C95391C[2],
	&matlist_00579C94[0],
	&material_8D455980FE9A6F043AF[0],
	&material_8D455980FE9A6F043AF[1],
	&material_8D455980FE9A6F043AF[2],
	&material_8D455980FE9A6F043AF[3],
	&material_8D455980FE9A6F043AF[4],
	&material_8D455980FE9A6F043AF[5],
	&material_8D4559811C9B8977DED[0],
	&material_8D45599A5D708A86372[0],
	&material_8D45599A5D708A86372[1],
	&material_8D45599ACF3F8224D1C[0],
	&material_8D4559813AA3F716A17[0],
	&matlist_00571D10[0],
	&material_8D45599A7DCF25E9B18[0],
	&material_8D45599A98F15891B68[0],
	&material_8D45599AB4CF8B1F7B5[0],
	&material_8D45599AB4CF8B1F7B5[1],
	&material_8D45599AB4CF8B1F7B5[2],
	&material_8D455981806F32B97A7[0],
	&material_8D455981806F32B97A7[1],
	&matlist_0056D3E8[0],
	&material_8D455981DC7CFFBB8FC[0],
	&material_8D45599C712248911C6[0],
	&material_8D45599C98158E99BE1[0],
	&material_8D45599CB0120B7C941[0],
	&material_8D45599CB0120B7C941[1],
	&material_8D45599CB0120B7C941[2],
	&material_8D455981A57F0B9445A[0],
	&material_8D455981A57F0B9445A[1],
	&matlist_0056E708[0],
	&material_8D455981C21E1FEB4AC[0],
	&material_8D45599B9C25AE3F0EA[0],
	&material_8D45599B5C4B87D2C2F[0],
	&material_8D45599AF041B2EA39E[0],
	&material_8D45599AF041B2EA39E[1],
	&material_8D45599AF041B2EA39E[2],
	&material_8D4559826913D3B51F9[0],
	&material_8D4559826913D3B51F9[1],
	&material_8D4559826913D3B51F9[2],
	&material_8D4559826913D3B51F9[3],
	&material_8D4559824D555EB9391[0],
	&material_8D4559824D555EB9391[1],
	&material_8D45599CEF6377DCE7C[0],
	&material_8D45599D1B8E446FC1D[0],
	&material_8D45599CD2ABF93600E[0],
	&material_8D45599CD2ABF93600E[1],
	&material_8D45599CD2ABF93600E[2],
	&material_8D4559820F8F7A3DB37[0],
	&material_8D4559820F8F7A3DB37[1],
	&material_8D4559820F8F7A3DB37[2],
	&material_8D4559820F8F7A3DB37[3],
	&material_8D455981F1CDDAA19D0[0],
	&material_8D455981F1CDDAA19D0[1],
	&matlist_8D4DE9097B6234C75B7[0],
	&matlist_8D4DE9097B6234C75B7[1],
	&matlist_8D4DE9097B6234C75B7[2],
	&matlist_8D4DE90567F26F882CF[0],
	&matlist_8D4DE90567F26F882CF[1],
	&matlist_8D4DE90567F26F882CF[2],
	&matlist_8D4DE8D511976FF28BD[0],
	&matlist_8D4DE8D511976FF28BD[1],
	&matlist_8D4DE8D511976FF28BD[2],
	&matlist_8D4DE861F87B4796B93[0],
	&matlist_8D4DE861F87B4796B93[1],
	&matlist_8D4DE861F87B4796B93[2],
	&matlist_8D4DE8523C17CC6772D[0],
	&matlist_8D4DE8523C17CC6772D[1],
	&matlist_8D4DE8523C17CC6772D[2],
	&matlist_8D4DE83B3002EF45102[0],
	&matlist_8D4DE83B3002EF45102[1],
	&matlist_8D4DE83B3002EF45102[2],
	&material_8D45B290FDD34751D31[0],
	&material_8D45B290FDD34751D31[1],
	&material_8D45B292644174E2C9F[0],
	&material_8D45B292644174E2C9F[1],
	&material_8D45DD42180F79C6C0D[0],
	&material_8D45DD42180F79C6C0D[1],
	&material_8D45B29685682B90577[0],
	&material_8D45B29685682B90577[1],
	&material_8D45B297FEEE52B8B4E[0],
	&material_8D45B297FEEE52B8B4E[1],
	&material_8D45DD457E9605D13AE[0],
	&material_8D45DD457E9605D13AE[1],
	&matlist_0000B68C[0],
	&matlist_0000B68C[1],
	&matlist_0000B68C[2],

	//Metal Sonic Materials
	&matlist_8D55B7D118592DBAB23[0],
	&matlist_8D55B7D16E366A94E23[0],
	&matlist_8D55B7D16E366A94E23[1],
	&matlist_8D55B7D22CB369ACD09[0],
	&matlist_8D55B7D22CB369ACD09[1],
	&matlist_8D55B7D22CB369ACD09[2],
	&matlist_8D55B7D4CD69DA45D9A[0],
	&matlist_8D55B7D4CD69DA45D9A[1],
	&matlist_8D55B7D4CD69DA45D9A[2],
	&matlist_8D55B7D1CA1362FB857[0],
	&matlist_8D55B7DDFED0D5D9370[0],
	&matlist_8D55B7DE4C2001ADD5A[0],
	&matlist_8D55B7DE4C2001ADD5A[1],
	&matlist_8D55B7DE4C2001ADD5A[2],
	&matlist_8D55B7DEE6DE16B776D[0],
	&matlist_8D55B7DEE6DE16B776D[1],
	&matlist_8D55B7DEE6DE16B776D[2],
	&matlist_8D55B7DEBD3F2EAD2F1[0],
	&matlist_8D55B7DEBD3F2EAD2F1[1],
	&matlist_8D55B7DEBD3F2EAD2F1[2],
	&matlist_8D55B7DE849D486F6B4[0],
	&matlist_8D55B7AA7C8826CEEB7[0],
	&matlist_8D55B7AAAC52BCF18C5[0],
	&matlist_8D55B7AAAC52BCF18C5[1],
	&matlist_8D55B7AAAC52BCF18C5[2],
	&matlist_8D55B7AB76E2BB3A8EE[0],
	&matlist_8D55B7AB41864833F33[0],
	&matlist_8D55B7AB23349B956BA[0],
	&matlist_8D55B7AB23349B956BA[1],
	&matlist_8D55B7AB23349B956BA[2],
	&matlist_8D55B7AAFF6E5E7C4A7[0],
	&matlist_8D55B7BF81BF26F0024[0],
	&matlist_8D55B7BFB85B71B70B3[0],
	&matlist_8D55B7BFB85B71B70B3[1],
	&matlist_8D55B7BFB85B71B70B3[2],
	&matlist_8D55B7C096E197DEFF4[0],
	&matlist_8D55B7C055B68284902[0],
	&matlist_8D55B7C01FB67A12012[0],
	&matlist_8D55B7C01FB67A12012[1],
	&matlist_8D55B7C01FB67A12012[2],
	&matlist_8D55B7BFE3DDC6C7D4B[0],
	&material_8D55B7A3530446F0991[0],
	&material_8D55B7A3530446F0991[1],
	&material_8D55B7A3530446F0991[2],
	&material_8D55B7A3530446F0991[3],
	&material_8D55B7A3530446F0991[4],
	&material_8D55B7A3530446F0991[5],
	&material_8D55B7A38789DEDC69C[0],
	&material_8D55B7A38789DEDC69C[1],
	&material_8D55B7A38789DEDC69C[2],
	&material_8D55B7A38789DEDC69C[3],
	&material_8D55B7A38789DEDC69C[4],
	&material_8D5116C3926D8D5906F[0],
	&material_8D5116C3BA15800DEB6[0],
	&material_8D5116C3BA15800DEB6[1],
	&material_8D5116BE293DDE1DEF2[0],
	&material_8D5116BE293DDE1DEF2[1],
	&material_8D5116BE293DDE1DEF2[2],
	&material_8D5116BE0A8816F0248[0],
	&material_8D5116BE0A8816F0248[1],
	&material_8D5116BE0A8816F0248[2],
	&material_8D5116C3DFE158B2CBE[0],
	&material_8D5116C3043A1A5A37C[0],
	&material_8D5116C33EA2214B41C[0],
	&material_8D5116C33EA2214B41C[1],
	&material_8D5116BF0847DC2166A[0],
	&material_8D5116BF0847DC2166A[1],
	&material_8D5116BF0847DC2166A[2],
	&material_8D5116BEBA32EC72570[0],
	&material_8D5116BEBA32EC72570[1],
	&material_8D5116BEBA32EC72570[2],
	&material_8D5116C361324ADDBE2[0],
	&material_8D5116BFAFDEB45D904[0],
	&material_8D5116BFD50968AB039[0],
	&material_8D5116BFD50968AB039[1],
	&material_8D5116BFD50968AB039[2],
	&material_8D5116C06D78A30A694[0],
	&material_8D5116C0AB6327155F9[1],
	&material_8D5116C02408BBC885F[0],
	&material_8D5116C02408BBC885F[1],
	&material_8D5116C02408BBC885F[2],
	&material_8D5116BFFC0B54D56ED[0],
	&material_8D5116C1C0CED7077A1[0],
	&material_8D5116C1E1E9721DF1B[0],
	&material_8D5116C1E1E9721DF1B[1],
	&material_8D5116C1E1E9721DF1B[2],
	&material_8D5116C2775C7842B41[0],
	&material_8D5116C253DF7A4E3E5[0],
	&material_8D5116C21F5EC47BAEB[0],
	&material_8D5116C21F5EC47BAEB[1],
	&material_8D5116C21F5EC47BAEB[2],
	&material_8D5116C20044E2E60D1[0],
	&material_8D5116BD49226C08BC9[0],
	&material_8D5116BD49226C08BC9[1],
	&material_8D5116BD49226C08BC9[2],
	&material_8D5116BD49226C08BC9[3],
	&material_8D5116BD49226C08BC9[4],
	&material_8D5116BD49226C08BC9[5],
	&material_8D5116BDB429733A462[0],
	&material_8D5116BDB429733A462[1],
	&material_8D5116BDB429733A462[2],
	&material_8D5116BDB429733A462[3],
	&material_8D5116BDB429733A462[4],
	&matlist_0058CD08[0],
	&matlist_0058F83C[0],
	&matlist_0058FAE0[0],
	&matlist_00597EA8[0],
	&matlist_0059A9D4[0],
	&matlist_0059AC78[0],
	&matlist_0059C268[0],

	//Knuckles Material Fixes
	&material_8D49E330C443CA61291[0],
	&material_8D49E330C443CA61291[1],
	&material_8D49E330C443CA61291[2],
	&material_8D49E330C443CA61291[3],
	&material_8D49E330C443CA61291[4],

	//Amy Material Fixes
	&material_8D4AD8CBDFCFE5DC5E7[0],
	&material_8D4AD8CBDFCFE5DC5E7[1],
	&material_8D4AD8CBDFCFE5DC5E7[2],
	&material_8D4AD8CBDFCFE5DC5E7[3],
	&material_8D4AD8CBDFCFE5DC5E7[4],
	&material_8D4DDBA25E4EB1EBB0F[0],
	&material_8D4DDBA25E4EB1EBB0F[1],
	&material_8D4AD8E518CB827EF9F[0],
	&material_8D4AD8E518CB827EF9F[1],
	&material_8D4AD8E518CB827EF9F[2],
	&material_8D4AD8E53D5C658C3BE[0],
	&material_8D4AD8E53D5C658C3BE[1],
	&material_8D4AD8E53D5C658C3BE[2],
	&material_8D4AD8E53D5C658C3BE[3],

	//Big Material Fixes
	&material_8D4DCB42FADA04DEFDC[0],
	&material_8D4CB1307C0B65BDDCF[0],
	&material_8D4CB129D9AC3A75E76[0],
	&material_8D4CB129D9AC3A75E76[1],
	&material_8D4CB129D9AC3A75E76[2],
	&material_8D4CB12950D75E95CA5[0],
	&material_8D4CB12950D75E95CA5[1],
	&material_8D4CB128B96FD40E733[0],
	&material_8D4CB128B96FD40E733[1],
	&material_8D4AD91D254FDC1DBD2[0],
	&material_8D4AD91B2897CD2EB94[0],
	&material_8D4AD91B2897CD2EB94[1],
	&material_8D4AD91B2897CD2EB94[2],
	&material_8D4AD91B2897CD2EB94[3],

	//Super Sonic Material Fixes
	&material_8D4559469C00BD8650C[0],
	&material_8D4559469C00BD8650C[1],
	&material_8D4559469C00BD8650C[2],
	&material_8D4559469C00BD8650C[3],
	&material_8D4559469C00BD8650C[0],
	&material_8D45594ECBF9842020C[0],
	&material_8D45594E29C8962BEDF[0],
	&material_8D45594D5026F36945C[0],
	&material_8D45594515B2EA7651B[0],
	&material_8D45594515B2EA7651B[1],
	&material_8D4559506FC499BABBA[0],
	&material_8D455945DD2BD93604F[0],
	&material_8D4559461176D83848C[0],
	&material_8D45594639A031C1B14[0],
	&material_8D45594639A031C1B14[1],
	&material_8D45594639A031C1B14[2],
	&material_8D45DC83129D328A0B3[0],
	&material_8D45DC83129D328A0B3[1],
	&material_8D45DC8353B24E7A972[0],
	&material_8D45DC8353B24E7A972[1],
	&material_8D45DC8330355079F55[0],
	&material_8D45594549A3932E69C[0],
	&material_8D4559456CDEA53E9A4[0],
	&material_8D455945880348F0E5C[0],
	&material_8D455945880348F0E5C[1],
	&material_8D455945880348F0E5C[2],
	&material_8D45DC820E06D6BB572[0],
	&material_8D45DC820E06D6BB572[1],
	&material_8D45DC8247365910C0C[0],
	&material_8D45DC8247365910C0C[1],
	&material_8D45DC82AFAF0AAC4E7[0],
	&material_8D455947A84E4F37A4E[0],
	&material_8D455947DD6B475EE3A[0],
	&material_8D4559480838EFC6628[0],
	&material_8D4559480838EFC6628[1],
	&material_8D4559480838EFC6628[2],
	&material_8D455948968E9144EBD[0],
	&material_8D455948968E9144EBD[1],
	&material_8D455948968E9144EBD[2],
	&material_8D455948968E9144EBD[3],
	&material_8D455948968E9144EBD[4],
	&material_8D455948AC9B6BFEE39[0],
	&material_8D455948AC9B6BFEE39[1],
	&material_8D455948AC9B6BFEE39[2],
	&material_8D45594827ECA299216[0],
	&material_8D4559484B7846D15FD[0],
	&material_8D45594876D38B511BE[0],
	&material_8D45594876D38B511BE[1],
	&material_8D45594876D38B511BE[2],
	&material_8D455948CD45B76EA23[0],
	&material_8D455948CD45B76EA23[1],
	&material_8D455948CD45B76EA23[2],
	&material_8D455948CD45B76EA23[3],
	&material_8D455948CD45B76EA23[4],
	&material_8D455948E41855F1077[0],
	&material_8D455948E41855F1077[1],
	&material_8D455948E41855F1077[2],

	//Event Stuff
	//TR1 Fixes
	&material_8D47043946447123A04[0],
	&material_8D47043946447123A04[1],
	&material_8D470436E94C4D7B904[0],
	&material_8D470436E94C4D7B904[1],
	&material_8D47043971B0CCE5880[0],
	&material_8D470436BBEDDE61BF3[0],
	&material_8D470435EF9F1294B1B[0],
	&material_8D470435EF9F1294B1B[1],
	&material_8D47043618B05E86AB4[0],
	&material_8D4704399D0E827EA21[0],
	&material_8D47043A4ADACCF377B[0],
	&material_8D47043A4ADACCF377B[1],
	&material_8D47043A886889A598E[0],
	&material_8D470437145BE1E4FE8[0],
	&material_8D4704374092E394F8D[0],
	&material_8D4704374092E394F8D[1],
	&material_8D47043770BCB221B23[0],
	&material_8D470435C319EFA501F[0],
	&material_8D470435C319EFA501F[1],
	&material_8D470435C319EFA501F[2],
	&material_8D470435C319EFA501F[3],
	&material_8D470435C319EFA501F[4],
	&material_8D4704318652107447A[0],
	&material_8D4704318652107447A[1],
	&material_8D4704337D27B04548F[0],
	&material_8D47043362D29494675[0],
	&material_8D47043362D29494675[1],
	&material_8D47043343F5BCEA273[0],
	&material_8D47043209B25BE0FC5[0],
	&material_8D470431E10A0C79291[0],
	&material_8D470431E10A0C79291[1],
	&material_8D470431BA2F30D48B4[0],
	&material_8D4704315E91B3786D4[0],
	&material_8D4704315E91B3786D4[1],
	&material_8D4704315E91B3786D4[2],
	&material_8D4704315E91B3786D4[3],
	&material_8D47042EA72D43C6BC0[0],
	&material_8D47042EA72D43C6BC0[1],

	//Tikal
	&matlist_00002884[0],
};

NJS_MATERIAL* Specular3[] = {
	//Tails intro
	&matlist_02F37A50[0],
	&matlist_02F37A50[3],
	&matlist_02F37A50[5],
	&matlist_02F37A50[9],
	&matlist_02F36AE8[0],
	&matlist_02F36AE8[1],
	&matlist_02F36AE8[2],
	&matlist_02F36AE8[3],

	//Knuckles Material Fixes
	&material_8D49E33095E01C8B132[2],

	//Gamma Material Fixes
	materials_001FD8E8[0],

	//Event
	//TR1 Model
	&material_8D47042E09EA9D5D092[0],
	&material_8D47042E09EA9D5D092[1],
	&material_8D47042E09EA9D5D092[2],
	&material_8D47042E09EA9D5D092[3],
	&material_8D47042E09EA9D5D092[4],
	&material_8D47042E09EA9D5D092[5],
	&material_8D47042E09EA9D5D092[6],
	&material_8D47042E09EA9D5D092[7],
	&material_8D47042E09EA9D5D092[8],
	&material_8D47042E09EA9D5D092[9],
	&material_8D47042E09EA9D5D092[10],
	&material_8D47042E09EA9D5D092[11],
	&material_8D47042E09EA9D5D092[12],
	&material_8D47042E09EA9D5D092[13],
	&material_8D47042E09EA9D5D092[14],
	&material_8D47042E09EA9D5D092[15],
	&material_8D47042E09EA9D5D092[16],
	&material_8D47042E09EA9D5D092[17],
	&material_8D47042E09EA9D5D092[18],
	&material_8D47042E09EA9D5D092[19],
	&material_8D47042E09EA9D5D092[20],
	&material_8D47042E09EA9D5D092[21],
	&material_8D47042E09EA9D5D092[22],
	&material_8D47042E09EA9D5D092[23],
	&material_8D47042E09EA9D5D092[24],
	&material_8D47042E09EA9D5D092[25],
	&material_8D47042E09EA9D5D092[26],
	&material_8D47042E09EA9D5D092[27],
	&material_8D47042E09EA9D5D092[28],
	&material_8D47042E09EA9D5D092[29],
	&material_8D47042E09EA9D5D092[30],
	&material_8D47042EF73446CA83B[0],
	&material_8D47042EF73446CA83B[1],
	&material_8D4704368516FAD610A[0],
	&material_8D4704368516FAD610A[1],
	&material_8D4704368516FAD610A[2],
	&material_8D4704368516FAD610A[3],
	&material_8D4704368516FAD610A[4],
	&material_8D4704365E4FA77C9AF[0],
	&material_8D4704365E4FA77C9AF[1],
	&material_8D4704365E4FA77C9AF[2],
	&material_8D4704365E4FA77C9AF[3],
	&material_8D4704365E4FA77C9AF[4],

	//Tornado 2 (Event)
	&matlist_00016068[0],
	&matlist_00016068[1],
	&matlist_000159C8[0],
	&matlist_000159C8[1],
	&matlist_000159C8[2],

	//Tornado 2 Change
	&material_8D4714ACE7FAE0BE986[0],
	&material_8D4714ACE7FAE0BE986[1],

	//EV Eggmobile 0
	&matlist_0006D138[0],
	&matlist_0006D138[1],
	&matlist_0006D138[2],
	&matlist_0006D138[3],
	&matlist_0006D138[4],
	&matlist_0006D138[5],
	&matlist_0006D138[6],
	&matlist_0006D138[7],
	&matlist_0006D138[8],
	&matlist_0006D138[9],
	&matlist_0006D138[10],
	&matlist_0006D138[11],
	&matlist_0006D138[12],
	&matlist_0006D138[13],
	&matlist_0006D138[14],
	&matlist_0006D138[15],
	&matlist_0006D138[16],
	&matlist_0006D138[17],
	&matlist_0006D138[18],
	&matlist_0006D138[19],
	&matlist_0006D138[20],
	&matlist_0006D138[21],
	&matlist_0006D138[22],
	&matlist_0006D138[23],
	&matlist_0006D138[24],
};

NJS_MATERIAL* TailsBody[] = {
	&material_8D473DC643E7780853A[0],
	&material_8D473DC643E7780853A[1],
	&material_8D473DC643E7780853A[2],
	&material_8D473DC626DF6739765[0],
	&material_8D473DC626DF6739765[1],
	&material_8D473DC626DF6739765[2],
	&material_8D4738D60AEBA4D78DC[0],
	&material_8D4738D60AEBA4D78DC[1],
	&material_8D4738D60AEBA4D78DC[2],
	&material_8D4738D60AEBA4D78DC[3],
	&material_8D473BA8B669B962A8B[0],
	&material_8D473BA8DF42DD8E2C6[0],
	&material_8D473BA8FE0268C341F[0],
	&material_8D473BA8FE0268C341F[1],
	&material_8D473BA8FE0268C341F[2],
	&material_8D473BA82DEA51C0FB9[0],
	&material_8D473BA86EEBE5681A7[0],
	&material_8D473BA88C77CE271F0[0],
	&material_8D473BA88C77CE271F0[1],
	&material_8D473BA88C77CE271F0[2],
	&material_8D473BA7B2E9B3BBF17[0],
	&material_8D473BA7DACC3F3632A[0],
	&material_8D473BAAD19A858E1C5[0],
	&material_8D473BAB4883B747EB3[0],
	&material_8D473BAB4883B747EB3[1],
	&material_8D473BAB4883B747EB3[2],
	&material_8D473BAB2F70E44316B[0],
	&material_8D473BAB2F70E44316B[1],
	&material_8D473BA7F44F61D63C1[0],
	&material_8D473BA7F44F61D63C1[1],
	&material_8D473BA7F44F61D63C1[2],
	&material_8D473BA740A58A5DA53[0],
	&material_8D473BA76B2ED5DA37D[0],
	&material_8D473BAAB2572253DD8[0],
	&material_8D473BAB0E6C4282A8C[0],
	&material_8D473BAB0E6C4282A8C[1],
	&material_8D473BAB0E6C4282A8C[2],
	&material_8D473BAAF1AD70CED3C[0],
	&material_8D473BAAF1AD70CED3C[1],
	&material_8D473BA786B2B1FDCA2[0],
	&material_8D473BA786B2B1FDCA2[1],
	&material_8D473BA786B2B1FDCA2[2],
	&material_8D4738D46B83ABB7FA4[0],
	&material_8D4738D43DB75E07889[0],
	&material_8D4738D5844FAA4637C[0],
	&material_8D4738D5844FAA4637C[1],
	&material_8D4738D5844FAA4637C[2],
	&material_8D4738D5844FAA4637C[3],
	&material_8D473DC8D3277A01F43[0],
	&material_8D473DC8D3277A01F43[1],
	&material_8D473DC8D3277A01F43[2],
	&material_8D473DC8AA5A8B14D6A[0],
	&material_8D473DC8AA5A8B14D6A[1],
	&material_8D473DC8AA5A8B14D6A[2],
	&material_8D47390D931DB1A6BFA[0],
	&material_8D47390D931DB1A6BFA[1],
	&material_8D47390D931DB1A6BFA[2],
	&material_8D47390D931DB1A6BFA[3],
	&material_8D473C002C708A2DCF9[0],
	&material_8D473C00496C65CD9F2[0],
	&material_8D473C0066F0FB74130[0],
	&material_8D473C0066F0FB74130[1],
	&material_8D473C0066F0FB74130[2],
	&material_8D473BFFC668E1BA1DA[0],
	&material_8D473BFFE78ACFED42C[0],
	&material_8D473C00030758EA062[0],
	&material_8D473C00030758EA062[1],
	&material_8D473C00030758EA062[2],
	&material_8D473BFF077921F715B[0],
	&material_8D473BFF27601A90F6A[0],
	&material_8D473BFF6E68BCDE1D8[0],
	&material_8D473BFF8D19A1E9EDB[0],
	&material_8D473BFF8D19A1E9EDB[1],
	&material_8D473BFF8D19A1E9EDB[2],
	&material_8D473BFF54E329267C3[0],
	&material_8D473BFF54E329267C3[1],
	&material_8D473BFF3DD862CAA5A[0],
	&material_8D473BFF3DD862CAA5A[1],
	&material_8D473BFF3DD862CAA5A[2],
	&material_8D473BFE4153933C074[0],
	&material_8D473BFE725B9007C50[0],
	&material_8D473BFEC6ECC00B721[0],
	&material_8D473BFEE037BADD00C[0],
	&material_8D473BFEE037BADD00C[1],
	&material_8D473BFEE037BADD00C[2],
	&material_8D473BFEAC00441C94B[0],
	&material_8D473BFEAC00441C94B[1],
	&material_8D473BFE8B9A55AB437[0],
	&material_8D473BFE8B9A55AB437[1],
	&material_8D473BFE8B9A55AB437[2],
	&material_8D47390D1DAC7F7B2B6[0],
	&material_8D47390C8D7AC3F56DA[0],
	&material_8D47390D6A02A195BEF[0],
	&material_8D47390D6A02A195BEF[1],
	&material_8D47390D6A02A195BEF[2],
	&material_8D47390D6A02A195BEF[3],
	&material_8D473CED98E68CD0B73[0],
	&material_8D473CED98E68CD0B73[1],
	&material_8D473CED98E68CD0B73[2],
	&material_8D473CED787BBC5B074[0],
	&material_8D473CED787BBC5B074[1],
	&material_8D473CED787BBC5B074[2],
	&material_8D473CECA36E0AB081A[0],
	&material_8D473CECA36E0AB081A[1],
	&material_8D473CECA36E0AB081A[2],
	&material_8D473CF32377A54C513[0],
	&material_8D473CF32377A54C513[1],
	&material_8D473CF32377A54C513[2],
	&material_8D473CF369BF65BE56A[0],
	&material_8D473CF34F0B11A3401[0],
	&material_8D473CF1BD85FC8AF13[0],
	&material_8D473CF1BD85FC8AF13[1],
	&material_8D473CF1BD85FC8AF13[2],
	&material_8D473CF1DD1ED3F082E[0],
	&material_8D473CF2585A0AEC02C[0],
	&material_8D473CED29184ECC578[0],
	&material_8D473CED29184ECC578[1],
	&material_8D473CF09DB021968C1[0],
	&material_8D473CED0EE2F08AFB6[0],
	&material_8D473CED0EE2F08AFB6[1],
	&material_8D473CECF5BF064B3A3[0],
	&material_8D473CECF5BF064B3A3[1],
	&material_8D473CECF5BF064B3A3[2],
	&material_8D473CECDB7890CC781[0],
	&material_8D473CECC00D1F035DE[0],
	&material_8D473CF0861F1241E41[0],
	&material_8D473CEE84430512C38[0],
	&material_8D473CEE84430512C38[1],
	&material_8D473CEE6AB3AD42C7F[0],
	&material_8D473CEE6AB3AD42C7F[1],
	&material_8D473CEE51E53753CE4[0],
	&material_8D473CEE51E53753CE4[1],
	&material_8D473CEE51E53753CE4[2],
	&material_8D473CEE369711F711C[0],
	&material_8D473CEE1B3F28773EA[0],
	&material_8D473CF06A87ADDE933[0],
	&material_8D473CF0522BF88ED2A[0],
	&material_8D473CEC8556F6F81E6[0],
	&material_8D473CEC8556F6F81E6[1],
	&material_8D473CEC8556F6F81E6[2],
	&material_8D473CEC8556F6F81E6[3],
	&matlist_0043F4E8[0],
	&material_8D4738D7FA7F4070298[0],
	&material_8D4738D7FA7F4070298[1],
	&material_8D4738D7FA7F4070298[2],
	&material_8D4738D7FA7F4070298[3],
	&material_8D473DB6A369809A67A[0],
	&material_8D473DB6A369809A67A[1],
	&material_8D473DB6A369809A67A[2],
	&material_8D473DBA62C70BB2467[0],
	&material_8D473DBA62C70BB2467[1],
	&material_8D473DBA62C70BB2467[2],
	&material_8D473DF29CC9DCACDB6[0],
	&material_8D473DF29CC9DCACDB6[1],
	&material_8D473DF29CC9DCACDB6[2],
	&material_8D473DC02D9DB80E59B[0],
	&material_8D473DC02D9DB80E59B[1],
	&material_8D473DC02D9DB80E59B[2],
	&material_8D473DF271EB1CE7E59[0],
	&material_8D473DF271EB1CE7E59[1],
	&material_8D473DF271EB1CE7E59[2],
	&material_8D47398CCD568858275[0],
	&material_8D47398CCD568858275[1],
	&material_8D47398CCD568858275[2],
	&material_8D47398CCD568858275[3],
	&material_8D47398CCD568858275[4],
	&material_8D47398CCD568858275[5],
	&material_8D4744FB57407D76E58[0],
	&material_8D4744FB57407D76E58[0],
	&material_8D4744FBE61785E97DD[0],
	&material_8D4744FBE61785E97DD[1],
	&material_8D4744FBE61785E97DD[2],
	&material_8D4744FBE61785E97DD[3],
	&material_8D4744FBE61785E97DD[4],
	&material_8D4744FBE61785E97DD[5],
	&material_8D4744FBE61785E97DD[6],
	&material_8D4744FBE61785E97DD[7],
};

NJS_MATERIAL* TailsShoes[] = {
	&material_8D473BAA6CA9332C47A[0],
	&material_8D473BAA6CA9332C47A[1],
	&material_8D473BA9380B3752C10[0],
	&material_8D473BA9380B3752C10[1],
	&material_8D473CE22D9DE010DD7[0],
	&material_8D473CE22D9DE010DD7[1],
	&material_8D473CE68A0107D97AA[0],
	&material_8D473CE68A0107D97AA[1],
	&material_8D473CE20A3E2E8099F[0],
	&material_8D473CE20A3E2E8099F[1],
	&material_8D473CE20A3E2E8099F[2],
	&material_8D473CE20A3E2E8099F[3],
	&material_8D473CE20A3E2E8099F[4],
	&material_8D473CE20A3E2E8099F[5],
	&material_8D473CE20A3E2E8099F[6],
	&material_8D473CE674B02CEF9B9[0],
	&material_8D473CE674B02CEF9B9[1],
	&material_8D473CE674B02CEF9B9[2],
	&material_8D473CE674B02CEF9B9[3],
	&material_8D473CE674B02CEF9B9[4],
	&material_8D473CE674B02CEF9B9[5],
	&material_8D473CE674B02CEF9B9[6],
	&material_8D473BAA53BFE1CA22F[0],
	&material_8D473BAA53BFE1CA22F[1],
	&material_8D473BA91E15540678B[0],
	&material_8D473BA91E15540678B[1],
	&material_8D473C01401D6C8E244[0],
	&material_8D473C01401D6C8E244[1],
	&material_8D473C0089700DBFF86[0],
	&material_8D473C0089700DBFF86[1],
	&material_8D473CED467AB5E5E08[0],
	&material_8D473CED467AB5E5E08[1],
	&material_8D473CEE9EC41378938[0],
	&material_8D473CEE9EC41378938[1],
	&material_8D473C015E23690715D[0],
	&material_8D473C015E23690715D[1],
	&material_8D473C00A4134A9C918[0],
	&material_8D473C00A4134A9C918[1],
	&material_8D473CED5B4065C9AC9[0],
	&material_8D473CED5B4065C9AC9[1],
	&material_8D473CEEB3CE205889C[0],
	&material_8D473CEEB3CE205889C[1],
	&matlist_0043F4E8[0], //Jumpball
};

void ForceIgnoreSpecular_Object(NJS_OBJECT *obj, bool recursive)
{
	if (obj)
	{
		if (obj->basicdxmodel)
		{
			for (int k = 0; k < obj->basicdxmodel->nbMat; ++k)
			{
				if (!(obj->basicdxmodel->mats[k].attrflags & NJD_FLAG_IGNORE_SPECULAR)) obj->basicdxmodel->mats[k].attrflags |= NJD_FLAG_IGNORE_SPECULAR;
			}
		}
		if (recursive && obj->child) ForceIgnoreSpecular_Object(obj->child, true);
		if (recursive && obj->sibling) ForceIgnoreSpecular_Object(obj->sibling, true);
	}
}

void ForceSpecular_Object(NJS_OBJECT *obj, bool recursive)
{
	if (obj)
	{
		if (obj->basicdxmodel)
		{
			for (int k = 0; k < obj->basicdxmodel->nbMat; ++k)
			{
				obj->basicdxmodel->mats[k].specular.color = 0xFFFFFFFF;
				if (obj->basicdxmodel->mats[k].attrflags & NJD_FLAG_IGNORE_SPECULAR)
				{
					obj->basicdxmodel->mats[k].attrflags &= ~NJD_FLAG_IGNORE_SPECULAR;
				}
			}
		}
		if (recursive && obj->child) ForceSpecular_Object(obj->child, true);
		if (recursive && obj->sibling) ForceSpecular_Object(obj->sibling, true);
	}
}

bool ForceDiffuse0Specular0(NJS_MATERIAL* material, Uint32 flags)
{
	set_diffuse(0, false);
	set_specular(0, false);
	use_default_diffuse(true);
	return true;
}

bool ForceDiffuse0Specular1(NJS_MATERIAL* material, Uint32 flags)
{
		set_diffuse(0, false);
		set_specular(1, false);
		return true;
}

bool ForceDiffuse0Specular0_Tails(NJS_MATERIAL* material, Uint32 flags)
{
	if (CurrentLevel == 1 && CurrentAct == 1 && TailsAI_ptr == nullptr && EV_MainThread_ptr == nullptr)
	{
		set_diffuse(0, false);
		set_specular(0, false);
	}
	else
	{
		set_diffuse(2, false);
		set_specular(2, false);
	}
	return true;
}

bool ForceDiffuse0Specular1_Tails(NJS_MATERIAL* material, Uint32 flags)
{
	if (CurrentLevel == 1 && CurrentAct == 1 && TailsAI_ptr == nullptr && EV_MainThread_ptr == nullptr)
	{
		set_diffuse(0, false);
		set_specular(1, false);
	}
	else
	{
		set_diffuse(2, false);
		set_specular(3, false);
	}
	return true;
}

bool ForceDiffuse2Specular2(NJS_MATERIAL* material, Uint32 flags)
{
	set_diffuse(2, false);
	set_specular(2, false);
	return true;
}

bool ForceDiffuse2Specular3(NJS_MATERIAL* material, Uint32 flags)
{
	set_diffuse(2, false);
	set_specular(3, false);
	return true;
}

void RemoveMaterialColors(NJS_OBJECT *obj)
{
	if (obj->basicdxmodel)
	{
		for (int q = 0; q < obj->basicdxmodel->nbMat; ++q)
		{
			obj->basicdxmodel->mats[q].diffuse.argb.r = 0xFF;
			obj->basicdxmodel->mats[q].diffuse.argb.g = 0xFF;
			obj->basicdxmodel->mats[q].diffuse.argb.b = 0xFF;
		}
	}
	if (obj->child) RemoveMaterialColors(obj->child);
	if (obj->sibling) RemoveMaterialColors(obj->sibling);
}

void ForceDiffuse2Specular2_Object(NJS_OBJECT *obj)
{
	if (obj->basicdxmodel)
	{
		for (int q = 0; q < obj->basicdxmodel->nbMat; ++q)
		{
			if (!(obj->basicdxmodel->mats[q].attrflags & NJD_FLAG_IGNORE_LIGHT))
			{
				TemporaryMaterialArray[0] = &obj->basicdxmodel->mats[q];
				material_register(TemporaryMaterialArray, 1, ForceDiffuse2Specular2);
			}
		}
	}
	if (obj->child) ForceDiffuse2Specular2_Object(obj->child);
	if (obj->sibling) ForceDiffuse2Specular2_Object(obj->sibling);
}

//Character Init Functions
void Init_Sonic()
{
	SONIC_OBJECTS[0] = &object_0056AF50;
	SONIC_OBJECTS[1] = &object_00563B7C;
	SONIC_OBJECTS[2] = &object_00563D0C;
	SONIC_OBJECTS[3] = &object_005654EC;
	SONIC_OBJECTS[4] = &object_00564CD0;
	SONIC_OBJECTS[5] = &object_005647B8;
	SONIC_OBJECTS[6] = &object_00564A78;
	SONIC_OBJECTS[7] = &object_00561F14;
	SONIC_OBJECTS[8] = &object_005620A4;
	SONIC_OBJECTS[9] = &object_005638CC;
	SONIC_OBJECTS[10] = &object_005630B0;
	SONIC_OBJECTS[11] = &object_00562B80;
	SONIC_OBJECTS[12] = &object_0056044C;
	SONIC_OBJECTS[13] = &object_005605DC;
	SONIC_OBJECTS[14] = &object_00561C68;
	SONIC_OBJECTS[15] = &object_005613F8;
	SONIC_OBJECTS[16] = &object_00560DD0;
	SONIC_OBJECTS[17] = &object_0055E99C;
	SONIC_OBJECTS[18] = &object_0055EB2C;
	SONIC_OBJECTS[19] = &object_005601B8;
	SONIC_OBJECTS[20] = &object_0055F948;
	SONIC_OBJECTS[21] = &object_0055F330;
	SONIC_OBJECTS[22] = &object_0062DE88;
	SONIC_OBJECTS[23] = &object_00626AB4;
	SONIC_OBJECTS[24] = &object_00626C44;
	SONIC_OBJECTS[25] = &object_0062840C;
	SONIC_OBJECTS[26] = &object_00627BF0;
	SONIC_OBJECTS[27] = &object_006276D8;
	SONIC_OBJECTS[28] = &object_00624E3C;
	SONIC_OBJECTS[29] = &object_00624FCC;
	SONIC_OBJECTS[30] = &object_006267F4;
	SONIC_OBJECTS[31] = &object_00625FD8;
	SONIC_OBJECTS[32] = &object_00625AA8;
	SONIC_OBJECTS[33] = &object_00623474;
	SONIC_OBJECTS[34] = &object_00623604;
	SONIC_OBJECTS[35] = &object_00624B78;
	SONIC_OBJECTS[36] = &object_00624308;
	SONIC_OBJECTS[37] = &object_00623C14;
	SONIC_OBJECTS[38] = &object_00621AC4;
	SONIC_OBJECTS[39] = &object_00621C54;
	SONIC_OBJECTS[40] = &object_006231E0;
	SONIC_OBJECTS[41] = &object_00622970;
	SONIC_OBJECTS[42] = &object_00622254;
	SONIC_OBJECTS[44] = &object_0057BC44;
	SONIC_OBJECTS[45] = &object_0056998C;
	SONIC_OBJECTS[46] = &object_00569594;
	SONIC_OBJECTS[47] = &object_005812AC;
	SONIC_OBJECTS[48] = &object_00569DEC;
	SONIC_OBJECTS[49] = &object_00569594;
	SONIC_OBJECTS[50] = &object_00569E20;
	SONIC_OBJECTS[51] = &object_00569CE8;
	SONIC_OBJECTS[52] = &object_005698F0;
	SONIC_OBJECTS[54] = &object_006837E8;
	SONIC_OBJECTS[55] = &object_00682EF4;
	SONIC_OBJECTS[58] = &object_00581FB8;
	SONIC_OBJECTS[59] = &object_005818AC;
	SONIC_OBJECTS[60] = &object_00582CC0;
	SONIC_OBJECTS[61] = &object_005825A4;
	SONIC_OBJECTS[62] = &object_00565520;
	SONIC_OBJECTS[63] = &object_00583284;
	SONIC_OBJECTS[64] = &object_00583904;
	SONIC_OBJECTS[65] = &object_00585EB4;
	SONIC_OBJECTS[66] = &object_005729CC;
	SONIC_OBJECTS[67] = &object_0057BC44;
	SONIC_ACTIONS[0]->object = &object_0056AF50;
	SONIC_ACTIONS[1]->object = &object_0056AF50;
	SONIC_ACTIONS[2]->object = &object_0056AF50;
	SONIC_ACTIONS[3]->object = &object_0056AF50;
	SONIC_ACTIONS[4]->object = &object_0056AF50;
	SONIC_ACTIONS[5]->object = &object_0056AF50;
	SONIC_ACTIONS[6]->object = &object_0056AF50;
	SONIC_ACTIONS[7]->object = &object_0056AF50;
	SONIC_ACTIONS[8]->object = &object_0056AF50;
	SONIC_ACTIONS[9]->object = &object_0056AF50;
	SONIC_ACTIONS[10]->object = &object_0056AF50;
	SONIC_ACTIONS[11]->object = &object_0056AF50;
	SONIC_ACTIONS[12]->object = &object_0056AF50;
	SONIC_ACTIONS[13]->object = &object_0056AF50;
	SONIC_ACTIONS[14]->object = &object_005729CC;
	SONIC_ACTIONS[15]->object = &object_0056AF50;
	SONIC_ACTIONS[16]->object = &object_0056AF50;
	SONIC_ACTIONS[17]->object = &object_0056AF50;
	SONIC_ACTIONS[18]->object = &object_0056AF50;
	SONIC_ACTIONS[19]->object = &object_0056AF50;
	SONIC_ACTIONS[20]->object = &object_0056AF50;
	SONIC_ACTIONS[21]->object = &object_0057BC44;
	SONIC_ACTIONS[22]->object = &object_0056AF50;
	SONIC_ACTIONS[23]->object = &object_0056AF50;
	SONIC_ACTIONS[27]->object = &object_0056AF50;
	SONIC_ACTIONS[28]->object = &object_0056AF50;
	SONIC_ACTIONS[29]->object = &object_0056AF50;
	SONIC_ACTIONS[30]->object = &object_0056AF50;
	SONIC_ACTIONS[31]->object = &object_0056AF50;
	SONIC_ACTIONS[32]->object = &object_0056AF50;
	SONIC_ACTIONS[33]->object = &object_0056AF50;
	SONIC_ACTIONS[34]->object = &object_0056AF50;
	SONIC_ACTIONS[35]->object = &object_0056AF50;
	SONIC_ACTIONS[36]->object = &object_0056AF50;
	SONIC_ACTIONS[37]->object = &object_0056AF50;
	SONIC_ACTIONS[38]->object = &object_0056AF50;
	SONIC_ACTIONS[39]->object = &object_0056AF50;
	SONIC_ACTIONS[40]->object = &object_0056AF50;
	SONIC_ACTIONS[41]->object = &object_0056AF50;
	SONIC_ACTIONS[42]->object = &object_0056AF50;
	SONIC_ACTIONS[43]->object = &object_0056AF50;
	SONIC_ACTIONS[44]->object = &object_0056AF50;
	SONIC_ACTIONS[45]->object = &object_0056AF50;
	SONIC_ACTIONS[46]->object = &object_0056AF50;
	SONIC_ACTIONS[47]->object = &object_0056AF50;
	SONIC_ACTIONS[48]->object = &object_0056AF50;
	SONIC_ACTIONS[49]->object = &object_0056AF50;
	SONIC_ACTIONS[50]->object = &object_0056AF50;
	SONIC_ACTIONS[51]->object = &object_0056AF50;
	SONIC_ACTIONS[52]->object = &object_0056AF50;
	SONIC_ACTIONS[53]->object = &object_0056AF50;
	SONIC_ACTIONS[54]->object = &object_0056AF50;
	SONIC_ACTIONS[55]->object = &object_0056AF50;
	SONIC_ACTIONS[56]->object = &object_0056AF50;
	SONIC_ACTIONS[57]->object = &object_0056AF50;
	SONIC_ACTIONS[58]->object = &object_0056AF50;
	SONIC_ACTIONS[59]->object = &object_0056AF50;
	SONIC_ACTIONS[60]->object = &object_0056AF50;
	SONIC_ACTIONS[61]->object = &object_0056AF50;
	SONIC_ACTIONS[62]->object = &object_0056AF50;
	SONIC_ACTIONS[63]->object = &object_0056AF50;
	SONIC_ACTIONS[64]->object = &object_0056AF50;
	SONIC_ACTIONS[65]->object = &object_0056AF50;
	SONIC_ACTIONS[66]->object = &object_0056AF50;
	SONIC_ACTIONS[67]->object = &object_0056AF50;
	SONIC_ACTIONS[68]->object = &object_0056AF50;
	SONIC_ACTIONS[69]->object = &object_0056AF50;
	SONIC_ACTIONS[70]->object = &object_0056AF50;
	SONIC_ACTIONS[71]->object = &object_0056AF50;
	SONIC_ACTIONS[72]->object = &object_0056AF50;
	SONIC_ACTIONS[87]->object = &object_0056AF50;
	SONIC_ACTIONS[88]->object = &object_0056AF50;
	SONIC_ACTIONS[89]->object = &object_0056AF50;
	SONIC_ACTIONS[90]->object = &object_0056AF50;
	SONIC_ACTIONS[91]->object = &object_0056AF50;
	SONIC_ACTIONS[92]->object = &object_0056AF50;
	SONIC_ACTIONS[93]->object = &object_0056AF50;
	SONIC_ACTIONS[94]->object = &object_0056AF50;
	SONIC_ACTIONS[95]->object = &object_0056AF50;
	SONIC_ACTIONS[96]->object = &object_0056AF50;
	SONIC_ACTIONS[97]->object = &object_0056AF50;
	SONIC_ACTIONS[98]->object = &object_0056AF50;
	SONIC_ACTIONS[99]->object = &object_0056AF50;
	SONIC_ACTIONS[100]->object = &object_0056AF50;
	SONIC_ACTIONS[101]->object = &object_0056AF50;
	SONIC_ACTIONS[102]->object = &object_0056AF50;
	SONIC_ACTIONS[103]->object = &object_0056AF50;
	SONIC_ACTIONS[104]->object = &object_0056AF50;
	SONIC_ACTIONS[105]->object = &object_0056AF50;
	SONIC_ACTIONS[106]->object = &object_0056AF50;
	SONIC_ACTIONS[107]->object = &object_0056AF50;
	SONIC_ACTIONS[108]->object = &object_0056AF50;
	SONIC_ACTIONS[109]->object = &object_0056AF50;
	SONIC_ACTIONS[113]->object = &object_0056AF50;
	SONIC_ACTIONS[114]->object = &object_0056AF50;
	SONIC_ACTIONS[115]->object = &object_0056AF50;
	SONIC_ACTIONS[116]->object = &object_0056AF50;
	SONIC_ACTIONS[117]->object = &object_0056AF50;
	SONIC_ACTIONS[118]->object = &object_0056AF50;
	SONIC_ACTIONS[119]->object = &object_0056AF50;
	SONIC_ACTIONS[120]->object = &object_0056AF50;
	SONIC_ACTIONS[121]->object = &object_0056AF50;
	SONIC_ACTIONS[122]->object = &object_0056AF50;
	SONIC_ACTIONS[123]->object = &object_0056AF50;
	SONIC_ACTIONS[124]->object = &object_0056AF50;
	SONIC_ACTIONS[125]->object = &object_0056AF50;
	SONIC_ACTIONS[126]->object = &object_0056AF50;
	SONIC_ACTIONS[127]->object = &object_0056AF50;
	SONIC_ACTIONS[128]->object = &object_0056AF50;
	SONIC_ACTIONS[129]->object = &object_0056AF50;
	SONIC_ACTIONS[130]->object = &object_0062DE88;
	SONIC_ACTIONS[131]->object = &object_0062DE88;
	SONIC_ACTIONS[132]->object = &object_0062DE88;
	SONIC_ACTIONS[133]->object = &object_0062DE88;
	SONIC_ACTIONS[134]->object = &object_0056AF50;
	SONIC_ACTIONS[135]->object = &object_0056AF50;
	SONIC_ACTIONS[136]->object = &object_0056AF50;
	SONIC_ACTIONS[137]->object = &object_0056AF50;
	SONIC_ACTIONS[138]->object = &object_0062DE88;
	SONIC_ACTIONS[139]->object = &object_0062DE88;
	SONIC_ACTIONS[140]->object = &object_0062DE88;
	SONIC_ACTIONS[141]->object = &object_0062DE88;
	SONIC_ACTIONS[142]->object = &object_0062FE6C; //Super Sonic jumpball
	SONIC_ACTIONS[143]->object = &object_0062DE88;
	SONIC_ACTIONS[144]->object = &object_0062DE88;
	SONIC_ACTIONS[145]->object = &object_0056AF50;
	SONIC_ACTIONS[146]->object = &object_0056AF50;
	SONIC_ACTIONS[147]->object = &object_0056AF50;
	SONIC_ACTIONS[148]->object = &object_0056AF50;
	SONIC_MODELS[0] = &attach_0055F304;
	SONIC_MODELS[1] = &attach_00560DA4;
	SONIC_MODELS[2] = &attach_005735AC;
	SONIC_MODELS[3] = &attach_00573DFC;
	SONIC_MODELS[4] = &attach_0057464C;
	SONIC_MODELS[5] = &attach_0057525C;
	SONIC_MODELS[6] = &attach_00575AB4;
	SONIC_MODELS[7] = &attach_0057630C;
	SONIC_MODELS[8] = &attach_00569568;
	SONIC_MODELS[9] = &attach_00579C68;
	SONIC_MOTIONS[0] = &CinematicHead;
	WriteJump((void*)0x007D0B50, InitSonicWeldInfo_mod);
	WriteJump((void*)0x007D14D0, InitNPCSonicWeldInfo_mod);
	WriteData((NJS_OBJECT**)0x00664C3E, &OBJECT_SonicPointingFinger);
	WriteData((NJS_OBJECT**)0x0069E24B, &OBJECT_SonicPointingFinger);
	WriteData((NJS_OBJECT**)0x006D010C, &OBJECT_SonicPointingFinger);
	WriteData((NJS_OBJECT**)0x006D711E, &OBJECT_SonicPointingFinger);
	WriteData((NJS_TEXLIST**)0x55E65C, SSAura01);
	WriteData((NJS_TEXLIST**)0x55E751, SSAura01);
	WriteData((NJS_TEXLIST**)0x55E712, SSAura02);
	WriteData((NJS_TEXLIST**)0x55E7CD, SSWaterThing);
	WriteData((NJS_TEXLIST**)0x55F2B3, SSHomingTex1);
	WriteData((NJS_TEXLIST**)0x55F1D1, SSHomingTex1);
	WriteData((NJS_TEXLIST**)0x55F1DC, SSHomingTex2);
	WriteData((NJS_TEXLIST**)0x55F2BE, SSHomingTex2);
	WriteData((NJS_TEXLIST**)0x55F677, SSHomingTex2);
	WriteData((NJS_TEXLIST**)0x55F669, SSHomingTex3);
	SUPERSONIC_TEXLIST = SS_PVM;
}

void Init_Miles()
{
	MILES_OBJECTS[0] = &object_0042AD54;
	MILES_OBJECTS[1] = &object_00437C44;
	MILES_OBJECTS[2] = &object_0043F4B4;
	MILES_OBJECTS[3] = &object_0044148C;
	MILES_OBJECTS[4] = &object_0042ABE8;
	MILES_OBJECTS[5] = &object_00437AD8;
	MILES_OBJECTS[6] = &object_0042AC84;
	MILES_OBJECTS[7] = &object_00437B74;
	MILES_OBJECTS[8] = &object_00426ED0;
	MILES_OBJECTS[9] = &object_00426B90;
	MILES_OBJECTS[10] = &object_00433DC0;
	MILES_OBJECTS[11] = &object_00433A80;
	MILES_OBJECTS[12] = &object_0041E548;
	MILES_OBJECTS[13] = &object_0041EC90;
	MILES_OBJECTS[14] = &object_0041ED2C;
	MILES_OBJECTS[15] = &object_0041E5E4;
	MILES_OBJECTS[16] = &object_0042BC1C;
	MILES_OBJECTS[17] = &object_0042B4D4;
	MILES_OBJECTS[18] = &object_0042BBE8;
	MILES_OBJECTS[19] = &object_0042B4A0;
	MILES_OBJECTS[20] = &object_00424D00;
	MILES_OBJECTS[21] = &object_00424E94;
	MILES_OBJECTS[22] = &object_0042674C;
	MILES_OBJECTS[23] = &object_00422FD8;
	MILES_OBJECTS[24] = &object_0042316C;
	MILES_OBJECTS[25] = &object_00424A14;
	MILES_OBJECTS[26] = &object_0042182C;
	MILES_OBJECTS[27] = &object_004219BC;
	MILES_OBJECTS[28] = &object_00422CF0;
	MILES_OBJECTS[29] = &object_004200CC;
	MILES_OBJECTS[30] = &object_0042025C;
	MILES_OBJECTS[31] = &object_00421598;
	MILES_OBJECTS[32] = &object_004225C8;
	MILES_OBJECTS[33] = &object_00421FE4;
	MILES_OBJECTS[34] = &object_00420E70;
	MILES_OBJECTS[35] = &object_00420884;
	MILES_OBJECTS[36] = &object_00425E88;
	MILES_OBJECTS[37] = &object_00425C40;
	MILES_OBJECTS[38] = &object_00424158;
	MILES_OBJECTS[39] = &object_00423F10;
	MILES_OBJECTS[40] = &object_00431BF0;
	MILES_OBJECTS[41] = &object_00431D84;
	MILES_OBJECTS[42] = &object_0043363C;
	MILES_OBJECTS[43] = &object_0042FEC8;
	MILES_OBJECTS[44] = &object_0043005C;
	MILES_OBJECTS[45] = &object_00431904;
	MILES_OBJECTS[46] = &object_0042E71C;
	MILES_OBJECTS[47] = &object_0042E8AC;
	MILES_OBJECTS[48] = &object_0042FBE0;
	MILES_OBJECTS[49] = &object_0042CFBC;
	MILES_OBJECTS[50] = &object_0042D14C;
	MILES_OBJECTS[51] = &object_0042E488;
	MILES_OBJECTS[52] = &object_0042F4B8;
	MILES_OBJECTS[53] = &object_0042EED4;
	MILES_OBJECTS[54] = &object_0042DD60;
	MILES_OBJECTS[55] = &object_0042D774;
	MILES_OBJECTS[56] = &object_00432D78;
	MILES_OBJECTS[57] = &object_00432B30;
	MILES_OBJECTS[58] = &object_00431048;
	MILES_OBJECTS[59] = &object_00430E00;
	MILES_OBJECTS[60] = &object_0046E63C;
	MILES_OBJECTS[61] = &object_0046F46C;
	MILES_OBJECTS[62] = &object_0041FE04;
	MILES_OBJECTS[63] = &object_0042CCF4;
	MILES_OBJECTS[64] = &object_0046EE44;
	MILES_OBJECTS[65] = &object_0046FC84;
	MILES_OBJECTS[66] = &object_0042AC1C;
	MILES_OBJECTS[67] = &object_0042ABE8;
	MILES_OBJECTS[68] = &object_00437B0C;
	MILES_OBJECTS[69] = &object_00437AD8;
	MILES_OBJECTS[70] = &object_0044C724;
	MILES_ACTIONS[0]->object = &object_00437C44;
	MILES_ACTIONS[1]->object = &object_00437C44;
	MILES_ACTIONS[2]->object = &object_00437C44;
	MILES_ACTIONS[3]->object = &object_00437C44;
	MILES_ACTIONS[4]->object = &object_00437C44;
	MILES_ACTIONS[5]->object = &object_00437C44;
	MILES_ACTIONS[6]->object = &object_00437C44;
	MILES_ACTIONS[7]->object = &object_00437C44;
	MILES_ACTIONS[8]->object = &object_00437C44;
	MILES_ACTIONS[9]->object = &object_00437C44;
	MILES_ACTIONS[10]->object = &object_00437C44;
	MILES_ACTIONS[11]->object = &object_0042AD54;
	MILES_ACTIONS[12]->object = &object_0042AD54;
	MILES_ACTIONS[13]->object = &object_0042AD54;
	MILES_ACTIONS[14]->object = &object_0042AD54;
	MILES_ACTIONS[15]->object = &object_0042AD54;
	MILES_ACTIONS[16]->object = &object_0042AD54;
	MILES_ACTIONS[17]->object = &object_00437C44;
	MILES_ACTIONS[18]->object = &object_00437C44;
	MILES_ACTIONS[19]->object = &object_00437C44;
	MILES_ACTIONS[20]->object = &object_00437C44;
	MILES_ACTIONS[21]->object = &object_0042AD54;
	MILES_ACTIONS[22]->object = &object_0042AD54;
	MILES_ACTIONS[23]->object = &object_0042AD54;
	MILES_ACTIONS[24]->object = &object_0042AD54;
	MILES_ACTIONS[25]->object = &object_0042AD54;
	MILES_ACTIONS[26]->object = &object_0042AD54;
	MILES_ACTIONS[27]->object = &object_0042AD54;
	MILES_ACTIONS[28]->object = &object_0042AD54;
	MILES_ACTIONS[29]->object = &object_0042AD54;
	MILES_ACTIONS[30]->object = &object_0042AD54;
	MILES_ACTIONS[31]->object = &object_0042AD54;
	MILES_ACTIONS[32]->object = &object_0042AD54;
	MILES_ACTIONS[33]->object = &object_0042AD54;
	MILES_ACTIONS[34]->object = &object_0042AD54;
	MILES_ACTIONS[35]->object = &object_0042AD54;
	MILES_ACTIONS[36]->object = &object_0042AD54;
	MILES_ACTIONS[37]->object = &object_0042AD54;
	MILES_ACTIONS[38]->object = &object_0042AD54;
	MILES_ACTIONS[39]->object = &object_0042AD54;
	MILES_ACTIONS[40]->object = &object_0042AD54;
	MILES_ACTIONS[41]->object = &object_0042AD54;
	MILES_ACTIONS[42]->object = &object_0042AD54;
	MILES_ACTIONS[43]->object = &object_0042AD54;
	MILES_ACTIONS[44]->object = &object_0042AD54;
	MILES_ACTIONS[45]->object = &object_0042AD54;
	MILES_ACTIONS[46]->object = &object_0042AD54;
	MILES_ACTIONS[47]->object = &object_0042AD54;
	MILES_ACTIONS[48]->object = &object_0042AD54;
	MILES_ACTIONS[49]->object = &object_0042AD54;
	MILES_ACTIONS[50]->object = &object_0042AD54;
	MILES_ACTIONS[51]->object = &object_0042AD54;
	MILES_ACTIONS[52]->object = &object_0042AD54;
	MILES_ACTIONS[53]->object = &object_00437C44;
	MILES_ACTIONS[54]->object = &object_00437C44;
	MILES_ACTIONS[55]->object = &object_0042AD54;
	MILES_ACTIONS[56]->object = &object_0042AD54;
	MILES_ACTIONS[57]->object = &object_0042AD54;
	MILES_ACTIONS[58]->object = &object_0042AD54;
	MILES_ACTIONS[59]->object = &object_0042AD54;
	MILES_ACTIONS[60]->object = &object_0042AD54;
	MILES_ACTIONS[61]->object = &object_0042AD54;
	MILES_ACTIONS[62]->object = &object_0042AD54;
	MILES_ACTIONS[63]->object = &object_0042AD54;
	MILES_ACTIONS[64]->object = &object_0043F4B4;
	MILES_ACTIONS[65]->object = &object_0044148C;
	MILES_ACTIONS[66]->object = &object_0042AD54;
	MILES_ACTIONS[67]->object = &object_0042AD54;
	MILES_ACTIONS[68]->object = &object_0042AD54;
	MILES_ACTIONS[69]->object = &object_0042AD54;
	MILES_ACTIONS[70]->object = &object_0042AD54;
	MILES_ACTIONS[71]->object = &object_0042AD54;
	MILES_ACTIONS[72]->object = &object_0042AD54;
	MILES_ACTIONS[73]->object = &object_0042AD54;
	MILES_ACTIONS[74]->object = &object_0042AD54;
	MILES_ACTIONS[75]->object = &object_0042AD54;
	MILES_ACTIONS[76]->object = &object_0042AD54;
	MILES_ACTIONS[77]->object = &object_0042AD54;
	MILES_ACTIONS[78]->object = &object_0042AD54;
	MILES_ACTIONS[79]->object = &object_0042AD54;
	MILES_ACTIONS[80]->object = &object_0042AD54;
	MILES_ACTIONS[81]->object = &object_0042AD54;
	MILES_ACTIONS[82]->object = &object_0042AD54;
	MILES_ACTIONS[83]->object = &object_0042AD54;
	MILES_ACTIONS[85]->object = &object_0042AD54;
	MILES_ACTIONS[86]->object = &object_0042AD54;
	MILES_ACTIONS[87]->object = &object_0042AD54;
	MILES_ACTIONS[88]->object = &object_0042AD54;
	MILES_ACTIONS[91]->object = &object_0042AD54;
	MILES_ACTIONS[92]->object = &object_0042AD54;
	MILES_ACTIONS[93]->object = &object_0042AD54;
	MILES_ACTIONS[94]->object = &object_0042AD54;
	MILES_ACTIONS[95]->object = &object_0042AD54;
	MILES_ACTIONS[96]->object = &object_0042AD54;
	MILES_ACTIONS[97]->object = &object_0042AD54;
	MILES_ACTIONS[110]->object = &object_0042AD54;
	MILES_ACTIONS[111]->object = &object_0042AD54;
	MILES_ACTIONS[112]->object = &object_0042AD54;
	MILES_ACTIONS[113]->object = &object_0042AD54;
	MILES_MODELS[0] = &attach_0041FDD8;
	MILES_MODELS[1] = &attach_0042CCC8;
	MILES_MODELS[2] = &attach_0042ABBC;
	MILES_MODELS[3] = &attach_00437AAC;
	MILES_MODELS[4] = &attach_0044517C;
	MILES_MODELS[5] = &attach_0041E51C;
	MILES_MODELS[6] = &attach_0041EC64;
	MILES_MODELS[7] = &attach_0042B40C;
	MILES_MODELS[8] = &attach_0042BB54;
	MILES_MODELS[9] = &attach_00445778;
	MILES_MODELS[10] = &attach_00445DA8;
	MILES_MODELS[11] = &attach_00446A08;
	MILES_MODELS[12] = &attach_00447038;
	MILES_MODELS[13] = &attach_004463D8;
	MILES_MODELS[14] = &attach_0046DFE8;
	MILES_MOTIONS[0] = &TailsCinematicHead;
	WriteData((NJS_OBJECT**)0x7D2186, &JetAnklet);
	WriteJump((void*)0x0045B840, Tails_Jiggle_mod);
	WriteJump((void*)0x007C6D80, InitTailsWeldInfo_mod);
	WriteJump((void*)0x007C7560, InitNPCTailsWeldInfo_mod);
	//Material fixes for the cutscene where Sonic sees Tails crash
	RemoveMaterialColors((NJS_OBJECT*)0x3175528); //Tails' model
	((NJS_OBJECT*)0x317178C)->basicdxmodel->mats[1].attrflags &= ~NJD_FLAG_USE_ALPHA; //Unnecessary alpha in Tails' arm
	((NJS_OBJECT*)0x31708E4)->basicdxmodel->mats[1].attrflags &= ~NJD_FLAG_USE_ALPHA; //Unnecessary alpha in Tails' arm
	((NJS_OBJECT*)0x31793C0)->basicdxmodel->mats[3].attrflags &= ~NJD_FLAG_IGNORE_SPECULAR; //Plane
	((NJS_OBJECT*)0x31793C0)->basicdxmodel->mats[5].attrflags &= ~NJD_FLAG_IGNORE_SPECULAR; //Plane
	((NJS_OBJECT*)0x31793C0)->basicdxmodel->mats[9].attrflags &= ~NJD_FLAG_IGNORE_SPECULAR; //Plane
	//Tails Upgrades
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
}

void Init_Knux()
{
	KNUCKLES_OBJECTS[0] = &object_002E23B0;
	KNUCKLES_OBJECTS[1] = &object_002EEE50;
	KNUCKLES_OBJECTS[2] = &object_002DB8A4;
	KNUCKLES_OBJECTS[3] = &object_002DBA34;
	KNUCKLES_OBJECTS[4] = &object_002DD0AC;
	KNUCKLES_OBJECTS[5] = &object_002DC244;
	KNUCKLES_OBJECTS[6] = &object_002D9E5C;
	KNUCKLES_OBJECTS[7] = &object_002D9FEC;
	KNUCKLES_OBJECTS[8] = &object_002DB5F4;
	KNUCKLES_OBJECTS[9] = &object_002DAB34;
	KNUCKLES_OBJECTS[10] = &object_002D876C;
	KNUCKLES_OBJECTS[11] = &object_002D88FC;
	KNUCKLES_OBJECTS[12] = &object_002D9BB0;
	KNUCKLES_OBJECTS[13] = &object_002D6FE4;
	KNUCKLES_OBJECTS[14] = &object_002D7174;
	KNUCKLES_OBJECTS[15] = &object_002D8438;
	KNUCKLES_OBJECTS[16] = &object_002D9754;
	KNUCKLES_OBJECTS[17] = &object_002D9088;
	KNUCKLES_OBJECTS[18] = &object_002D7FDC;
	KNUCKLES_OBJECTS[19] = &object_002D7900;
	KNUCKLES_OBJECTS[20] = &object_002DC94C;
	KNUCKLES_OBJECTS[21] = &object_002DC244;
	KNUCKLES_OBJECTS[22] = &object_002DAEE4;
	KNUCKLES_OBJECTS[23] = &object_002DAB34;
	KNUCKLES_OBJECTS[24] = &object_002E8324;
	KNUCKLES_OBJECTS[25] = &object_002E84B4;
	KNUCKLES_OBJECTS[26] = &object_002E9B2C;
	KNUCKLES_OBJECTS[27] = &object_002E8CC4;
	KNUCKLES_OBJECTS[28] = &object_002E68DC;
	KNUCKLES_OBJECTS[29] = &object_002E6A6C;
	KNUCKLES_OBJECTS[30] = &object_002E8074;
	KNUCKLES_OBJECTS[31] = &object_002E75B4;
	KNUCKLES_OBJECTS[32] = &object_002E51EC;
	KNUCKLES_OBJECTS[33] = &object_002E537C;
	KNUCKLES_OBJECTS[34] = &object_002E6630;
	KNUCKLES_OBJECTS[35] = &object_002E3A64;
	KNUCKLES_OBJECTS[36] = &object_002E3BF4;
	KNUCKLES_OBJECTS[37] = &object_002E4EB8;
	KNUCKLES_OBJECTS[38] = &object_002E61D4;
	KNUCKLES_OBJECTS[39] = &object_002E5B08;
	KNUCKLES_OBJECTS[40] = &object_002E4A5C;
	KNUCKLES_OBJECTS[41] = &object_002E4380;
	KNUCKLES_OBJECTS[42] = &object_002E93CC;
	KNUCKLES_OBJECTS[43] = &object_002E8CC4;
	KNUCKLES_OBJECTS[44] = &object_002E7964;
	KNUCKLES_OBJECTS[45] = &object_002E75B4;
	KNUCKLES_OBJECTS[46] = &object_00328878;
	KNUCKLES_OBJECTS[47] = &object_003291C4;
	KNUCKLES_OBJECTS[49] = &object_002E191C;
	KNUCKLES_OBJECTS[50] = &object_002EE3BC;
	KNUCKLES_OBJECTS[51] = &object_002E21A8;
	KNUCKLES_OBJECTS[52] = &object_002E2070;
	KNUCKLES_OBJECTS[53] = &object_002E1C78;
	KNUCKLES_OBJECTS[54] = &object_002E1D14;
	KNUCKLES_OBJECTS[55] = &object_002E191C;
	KNUCKLES_OBJECTS[56] = &object_0030257C;
	KNUCKLES_OBJECTS[58] = &object_002DB5F4;
	KNUCKLES_OBJECTS[59] = &object_002DAEE4;
	KNUCKLES_OBJECTS[60] = &object_002DAB34;
	KNUCKLES_OBJECTS[61] = &object_002DA324;
	KNUCKLES_OBJECTS[62] = &object_002DD0AC;
	KNUCKLES_OBJECTS[63] = &object_002DC94C;
	KNUCKLES_OBJECTS[64] = &object_002DC244;
	KNUCKLES_OBJECTS[65] = &object_002DC59C;
	KNUCKLES_OBJECTS[66] = &object_002E8074;
	KNUCKLES_OBJECTS[67] = &object_002E7964;
	KNUCKLES_OBJECTS[68] = &object_002E75B4;
	KNUCKLES_OBJECTS[69] = &object_002E6DA4;
	KNUCKLES_OBJECTS[70] = &object_002E9B2C;
	KNUCKLES_OBJECTS[71] = &object_002E93CC;
	KNUCKLES_OBJECTS[72] = &object_002E8CC4;
	KNUCKLES_OBJECTS[73] = &object_002E901C;
	KNUCKLES_ACTIONS[0]->object = &object_002E23B0;
	KNUCKLES_ACTIONS[1]->object = &object_002E23B0;
	KNUCKLES_ACTIONS[2]->object = &object_002EEE50;
	KNUCKLES_ACTIONS[3]->object = &object_002EEE50;
	KNUCKLES_ACTIONS[4]->object = &object_002EEE50;
	KNUCKLES_ACTIONS[5]->object = &object_002EEE50;
	KNUCKLES_ACTIONS[6]->object = &object_002E23B0;
	KNUCKLES_ACTIONS[7]->object = &object_002EEE50;
	KNUCKLES_ACTIONS[9]->object = &object_002E23B0;
	KNUCKLES_ACTIONS[10]->object = &object_002E23B0;
	KNUCKLES_ACTIONS[11]->object = &object_002E23B0;
	KNUCKLES_ACTIONS[12]->object = &object_002E23B0;
	KNUCKLES_ACTIONS[13]->object = &object_002E23B0;
	KNUCKLES_ACTIONS[14]->object = &object_002E23B0;
	KNUCKLES_ACTIONS[15]->object = &object_002EEE50;
	KNUCKLES_ACTIONS[16]->object = &object_002EEE50;
	KNUCKLES_ACTIONS[17]->object = &object_002EEE50;
	KNUCKLES_ACTIONS[18]->object = &object_002EEE50;
	KNUCKLES_ACTIONS[19]->object = &object_002EEE50;
	KNUCKLES_ACTIONS[20]->object = &object_002EEE50;
	KNUCKLES_ACTIONS[21]->object = &object_002EEE50;
	KNUCKLES_ACTIONS[22]->object = &object_002E23B0;
	KNUCKLES_ACTIONS[23]->object = &object_002E23B0;
	KNUCKLES_ACTIONS[24]->object = &object_002E23B0;
	KNUCKLES_ACTIONS[25]->object = &object_002E23B0;
	KNUCKLES_ACTIONS[26]->object = &object_002E23B0;
	KNUCKLES_ACTIONS[27]->object = &object_002E23B0;
	KNUCKLES_ACTIONS[28]->object = &object_002E23B0;
	KNUCKLES_ACTIONS[29]->object = &object_002E23B0;
	KNUCKLES_ACTIONS[30]->object = &object_002E23B0;
	KNUCKLES_ACTIONS[31]->object = &object_002E23B0;
	KNUCKLES_ACTIONS[32]->object = &object_002E23B0;
	KNUCKLES_ACTIONS[33]->object = &object_002E23B0;
	KNUCKLES_ACTIONS[34]->object = &object_002E23B0;
	KNUCKLES_ACTIONS[35]->object = &object_002EEE50;
	KNUCKLES_ACTIONS[36]->object = &object_002EEE50;
	KNUCKLES_ACTIONS[37]->object = &object_002EEE50;
	KNUCKLES_ACTIONS[38]->object = &object_002E23B0;
	KNUCKLES_ACTIONS[39]->object = &object_002EEE50;
	KNUCKLES_ACTIONS[40]->object = &object_002E23B0;
	KNUCKLES_ACTIONS[41]->object = &object_002E23B0;
	KNUCKLES_ACTIONS[42]->object = &object_002EEE50;
	KNUCKLES_ACTIONS[43]->object = &object_002E23B0;
	KNUCKLES_ACTIONS[44]->object = &object_002E23B0;
	KNUCKLES_ACTIONS[45]->object = &object_002E23B0;
	KNUCKLES_ACTIONS[46]->object = &object_002E23B0;
	KNUCKLES_ACTIONS[47]->object = &object_002E23B0;
	KNUCKLES_ACTIONS[48]->object = &object_002E23B0;
	KNUCKLES_ACTIONS[49]->object = &object_002E23B0;
	KNUCKLES_ACTIONS[50]->object = &object_002E23B0;
	KNUCKLES_ACTIONS[51]->object = &object_002E23B0;
	KNUCKLES_ACTIONS[52]->object = &object_002EEE50;
	KNUCKLES_ACTIONS[53]->object = &object_002E23B0;
	KNUCKLES_ACTIONS[54]->object = &object_002E23B0;
	KNUCKLES_ACTIONS[55]->object = &object_002E23B0;
	KNUCKLES_ACTIONS[56]->object = &object_002E23B0;
	KNUCKLES_ACTIONS[57]->object = &object_002EEE50;
	KNUCKLES_ACTIONS[58]->object = &object_002E23B0;
	KNUCKLES_ACTIONS[59]->object = &object_002E23B0;
	KNUCKLES_ACTIONS[60]->object = &object_002E23B0;
	KNUCKLES_ACTIONS[61]->object = &object_002F8530;
	KNUCKLES_ACTIONS[62]->object = &object_002F0E24;
	KNUCKLES_ACTIONS[63]->object = &object_002E23B0;
	KNUCKLES_ACTIONS[64]->object = &object_002E23B0;
	KNUCKLES_ACTIONS[65]->object = &object_002E23B0;
	KNUCKLES_ACTIONS[66]->object = &object_002E23B0;
	KNUCKLES_ACTIONS[67]->object = &object_002E23B0;
	KNUCKLES_ACTIONS[68]->object = &object_002E23B0;
	KNUCKLES_ACTIONS[69]->object = &object_002E23B0;
	KNUCKLES_ACTIONS[70]->object = &object_002E23B0;
	KNUCKLES_ACTIONS[71]->object = &object_002E23B0;
	KNUCKLES_ACTIONS[72]->object = &object_002E23B0;
	KNUCKLES_ACTIONS[73]->object = &object_002E23B0;
	KNUCKLES_ACTIONS[74]->object = &object_002E23B0;
	KNUCKLES_ACTIONS[75]->object = &object_002E23B0;
	KNUCKLES_ACTIONS[76]->object = &object_002E23B0;
	KNUCKLES_ACTIONS[77]->object = &object_002E23B0;
	KNUCKLES_ACTIONS[78]->object = &object_002E23B0;
	KNUCKLES_ACTIONS[79]->object = &object_002E23B0;
	KNUCKLES_ACTIONS[80]->object = &object_002E23B0;
	KNUCKLES_ACTIONS[81]->object = &object_002E23B0;
	KNUCKLES_ACTIONS[82]->object = &object_002E23B0;
	KNUCKLES_ACTIONS[83]->object = &object_002E23B0;
	KNUCKLES_ACTIONS[84]->object = &object_002E23B0;
	KNUCKLES_ACTIONS[85]->object = &object_002EEE50;
	KNUCKLES_ACTIONS[86]->object = &object_002E23B0;
	KNUCKLES_ACTIONS[87]->object = &object_002E23B0;
	KNUCKLES_ACTIONS[88]->object = &object_002E23B0;
	KNUCKLES_ACTIONS[89]->object = &object_002E23B0;
	KNUCKLES_MODELS[0] = &attach_003298C8;
	KNUCKLES_MODELS[1] = &attach_00329FF8;
	KNUCKLES_MODELS[2] = &attach_0032A6F0;
	KNUCKLES_MODELS[3] = &attach_0032ADF8;
	KNUCKLES_MODELS[4] = &attach_002E18F0;
	KNUCKLES_MODELS[5] = &attach_002EE390;
	KNUCKLES_MODELS[6] = &attach_002FC558;
	KNUCKLES_MODELS[7] = &attach_002DB5C8;
	KNUCKLES_MODELS[8] = &attach_002DAEB8;
	KNUCKLES_MODELS[9] = &attach_002DAB08;
	KNUCKLES_MODELS[10] = &attach_002DA2F8;
	KNUCKLES_MODELS[11] = &attach_002DD080;
	KNUCKLES_MODELS[12] = &attach_002DC920;
	KNUCKLES_MODELS[13] = &attach_002DC218;
	KNUCKLES_MODELS[14] = &attach_002DC570;
	KNUCKLES_MODELS[15] = &attach_0032C950;
	KNUCKLES_MODELS[16] = &attach_0032C2F8;
	KNUCKLES_MODELS[17] = &attach_0032BF48;
	KNUCKLES_MODELS[18] = &attach_0032B7C0;
	KNUCKLES_MODELS[19] = &attach_0032B488;
	KNUCKLES_MODELS[20] = &attach_0032D7E0;
	KNUCKLES_MODELS[21] = &attach_0032D430;
	KNUCKLES_MODELS[22] = &attach_0032CCA8;
	KNUCKLES_MOTIONS[0] = &KnucklesEV;
	WriteJump((void*)0x007C94D0, InitKnucklesWeldInfo_mod);
	WriteJump((void*)0x007C9C80, InitNPCKnucklesWeldInfo_mod);
	WriteData((uint16_t**)0x0472CAC, (uint16_t*)&Knuckles_ShovelClawIndices_DC);
	WriteData((uint16_t**)0x0472B2C, (uint16_t*)&Knuckles_HandIndices_DC);
	WriteData((uint16_t**)0x0472835, (uint16_t*)&Knuckles_HandIndices_DC);
}

void Init_Amy()
{
	AMY_OBJECTS[0] = &object_00016460;
	AMY_OBJECTS[1] = &object_00016E7C;
	AMY_OBJECTS[2] = &object_0000FB34;
	AMY_OBJECTS[3] = &object_0000F974;
	AMY_OBJECTS[4] = &object_000159CC;
	AMY_OBJECTS[5] = &object_00009C54;
	AMY_OBJECTS[6] = &object_0000EA74;
	AMY_OBJECTS[7] = &object_0000EC04;
	AMY_OBJECTS[8] = &object_000112C4;
	AMY_OBJECTS[9] = &object_0000CE6C;
	AMY_OBJECTS[10] = &object_0000CFFC;
	AMY_OBJECTS[11] = &object_0000D7B4;
	AMY_OBJECTS[12] = &object_0000B7D4;
	AMY_OBJECTS[13] = &object_0000B994;
	AMY_OBJECTS[14] = &object_0000CBC0;
	AMY_OBJECTS[15] = &object_0000A114;
	AMY_OBJECTS[16] = &object_0000A2D4;
	AMY_OBJECTS[17] = &object_0000B510;
	AMY_OBJECTS[18] = &object_0000C508;
	AMY_OBJECTS[19] = &object_0000BE90;
	AMY_OBJECTS[20] = &object_0000AE48;
	AMY_OBJECTS[21] = &object_0000A7D0;
	AMY_OBJECTS[22] = &object_00010AF8;
	AMY_OBJECTS[23] = &object_000108A0;
	AMY_OBJECTS[24] = &object_0000E7C8;
	AMY_OBJECTS[25] = &object_0000E570;
	AMY_OBJECTS[26] = &object_00016258;
	AMY_OBJECTS[27] = &object_00016120;
	AMY_OBJECTS[28] = &object_00015D28;
	AMY_OBJECTS[30] = &object_00015DC4;
	AMY_OBJECTS[31] = &object_000159CC;
	AMY_OBJECTS[32] = &object_00023300;
	AMY_OBJECTS[33] = &object_000159CC;
	AMY_OBJECTS[34] = &object_00012324;
	AMY_OBJECTS[35] = &object_0001D858;
	AMY_OBJECTS[36] = &object_0000FDF8;
	AMY_OBJECTS[37] = &object_0000FB34;
	AMY_OBJECTS[38] = &object_0001D204;
	AMY_ACTIONS[0]->object = &object_00016460;
	AMY_ACTIONS[1]->object = &object_00016460;
	AMY_ACTIONS[2]->object = &object_00016460;
	AMY_ACTIONS[3]->object = &object_00016460;
	AMY_ACTIONS[4]->object = &object_00016460;
	AMY_ACTIONS[5]->object = &object_00016460;
	AMY_ACTIONS[6]->object = &object_00016460;
	AMY_ACTIONS[7]->object = &object_00016460;
	AMY_ACTIONS[8]->object = &object_00016460;
	AMY_ACTIONS[9]->object = &object_00016460;
	AMY_ACTIONS[10]->object = &object_00016460;
	AMY_ACTIONS[11]->object = &object_00016460;
	AMY_ACTIONS[12]->object = &object_00016460;
	AMY_ACTIONS[13]->object = &object_00016460;
	AMY_ACTIONS[14]->object = &object_00016460;
	AMY_ACTIONS[15]->object = &object_00016460;
	AMY_ACTIONS[16]->object = &object_00016460;
	AMY_ACTIONS[17]->object = &object_00016460;
	AMY_ACTIONS[18]->object = &object_00016460;
	AMY_ACTIONS[19]->object = &object_00016460;
	AMY_ACTIONS[20]->object = &object_00016460;
	AMY_ACTIONS[21]->object = &object_00016460;
	AMY_ACTIONS[22]->object = &object_00016460;
	AMY_ACTIONS[23]->object = &object_00016460;
	AMY_ACTIONS[24]->object = &object_00016460;
	AMY_ACTIONS[25]->object = &object_00016460;
	AMY_ACTIONS[26]->object = &object_00016460;
	AMY_ACTIONS[27]->object = &object_00016460;
	AMY_ACTIONS[28]->object = &object_00016460;
	AMY_ACTIONS[29]->object = &object_00016460;
	AMY_ACTIONS[30]->object = &object_00016460;
	AMY_ACTIONS[31]->object = &object_00016460;
	AMY_ACTIONS[32]->object = &object_00016460;
	AMY_ACTIONS[33]->object = &object_00016460;
	AMY_ACTIONS[34]->object = &object_00016460;
	AMY_ACTIONS[35]->object = &object_00016460;
	AMY_ACTIONS[36]->object = &object_00016460;
	AMY_ACTIONS[37]->object = &object_00016460;
	AMY_ACTIONS[38]->object = &object_00016460;
	AMY_ACTIONS[39]->object = &object_00016460;
	AMY_ACTIONS[40]->object = &object_00016460;
	AMY_ACTIONS[41]->object = &object_00016460;
	AMY_ACTIONS[42]->object = &object_00016460;
	AMY_ACTIONS[43]->object = &object_00016460;
	AMY_ACTIONS[44]->object = &object_00016460;
	AMY_ACTIONS[45]->object = &object_00016460;
	AMY_ACTIONS[46]->object = &object_00016460;
	AMY_ACTIONS[47]->object = &object_00016460;
	AMY_ACTIONS[48]->object = &object_00016460;
	AMY_ACTIONS[49]->object = &object_00016460;
	AMY_ACTIONS[50]->object = &object_00016460;
	AMY_ACTIONS[51]->object = &object_00016460;
	AMY_ACTIONS[52]->object = &object_00016460;
	AMY_ACTIONS[53]->object = &object_00016460;
	AMY_ACTIONS[54]->object = &object_00016460;
	AMY_ACTIONS[55]->object = &object_00016460;
	AMY_ACTIONS[56]->object = &object_00016460;
	AMY_ACTIONS[57]->object = &object_00016460;
	AMY_ACTIONS[58]->object = &object_00016460;
	AMY_ACTIONS[59]->object = &object_00016460;
	AMY_ACTIONS[60]->object = &object_00016460;
	AMY_ACTIONS[61]->object = &object_00016460;
	AMY_ACTIONS[62]->object = &object_00016460;
	AMY_ACTIONS[63]->object = &object_00016460;
	AMY_ACTIONS[64]->object = &object_00016460;
	AMY_ACTIONS[65]->object = &object_00016460;
	AMY_ACTIONS[66]->object = &object_00016460;
	AMY_ACTIONS[67]->object = &object_00016460;
	AMY_ACTIONS[68]->object = &object_00016460;
	AMY_ACTIONS[69]->object = &object_00016460;
	AMY_ACTIONS[70]->object = &object_00016460;
	AMY_ACTIONS[71]->object = &object_00016460;
	AMY_ACTIONS[72]->object = &object_00016460;
	AMY_ACTIONS[73]->object = &object_00016460;
	AMY_ACTIONS[74]->object = &object_00016E7C;
	AMY_ACTIONS[75]->object = &object_00016E7C;
	AMY_ACTIONS[76]->object = &object_00016460;
	AMY_ACTIONS[77]->object = &object_00016460;
	AMY_ACTIONS[78]->object = &object_00016460;
	AMY_ACTIONS[79]->object = &object_00016460;
	AMY_MODELS[0] = &attach_00016DE8;
	AMY_MODELS[1] = &attach_000159A0;
	AMY_MODELS[2] = &attach_0001C100;
	AMY_MODELS[3] = &attach_00009C28;
	AMY_MODELS[4] = &attach_00018A90;
	AMY_MOTIONS[0] = &AmyEVHead_Motion;
	WriteData((NJS_OBJECT**)0x009858A4, &object_00584EE0);
	WriteJump((void*)0x007CCB90, InitAmyWeldInfo_mod);
	WriteJump((void*)0x007CD000, InitNPCAmyWeldInfo_mod);
}

void Init_Big()
{
	BIG_OBJECTS[0] = &object_0012541C;
	BIG_OBJECTS[1] = &object_0012CA3C;
	BIG_OBJECTS[2] = &object_00120834;
	BIG_OBJECTS[3] = &object_00120C14;
	BIG_OBJECTS[4] = &object_0012210C;
	BIG_OBJECTS[5] = &object_00121910;
	BIG_OBJECTS[6] = &object_0011DD6C;
	BIG_OBJECTS[7] = &object_0011E14C;
	BIG_OBJECTS[8] = &object_0011E6E4;
	BIG_OBJECTS[9] = &object_00120088;
	BIG_OBJECTS[10] = &object_001233D4;
	BIG_OBJECTS[11] = &object_0012414C;
	BIG_OBJECTS[12] = &object_00123EA0;
	BIG_OBJECTS[13] = &object_001239B4;
	BIG_OBJECTS[14] = &object_0012450C;
	BIG_OBJECTS[15] = &object_001247B4;
	BIG_OBJECTS[16] = &object_001252B0;
	BIG_OBJECTS[17] = &object_00124DBC;
	BIG_OBJECTS[18] = &object_00121B8C;
	BIG_OBJECTS[19] = &object_001291D4;
	BIG_OBJECTS[20] = &object_00120304;
	BIG_OBJECTS[22] = &object_0011D7A0;
	BIG_OBJECTS[23] = &object_0011B5FC;
	BIG_OBJECTS[24] = &object_0011B754;
	BIG_OBJECTS[25] = &object_0011F384;
	BIG_OBJECTS[26] = &object_0011D76C;
	BIG_OBJECTS[27] = &object_0011D448;
	BIG_OBJECTS[28] = &object_0012CA3C;
	BIG_OBJECTS[30] = &object_001291D4;
	BIG_OBJECTS[31] = &object_001284BC;
	BIG_OBJECTS[32] = &object_0011B0D0;
	BIG_OBJECTS[33] = &object_0011D808;
	BIG_OBJECTS[34] = &object_0011F384;
	BIG_OBJECTS[35] = &object_0011EC34;
	BIG_OBJECTS[36] = &object_00128A90;
	BIG_ACTIONS[0]->object = &object_0012541C;
	BIG_ACTIONS[1]->object = &object_0012541C;
	BIG_ACTIONS[2]->object = &object_0012541C;
	BIG_ACTIONS[4]->object = &object_0012541C;
	BIG_ACTIONS[5]->object = &object_0012541C;
	BIG_ACTIONS[6]->object = &object_0012541C;
	BIG_ACTIONS[7]->object = &object_0012541C;
	BIG_ACTIONS[8]->object = &object_0012541C;
	BIG_ACTIONS[9]->object = &object_0012541C;
	BIG_ACTIONS[10]->object = &object_0012541C;
	BIG_ACTIONS[11]->object = &object_0012541C;
	BIG_ACTIONS[12]->object = &object_0012541C;
	BIG_ACTIONS[13]->object = &object_0012541C;
	BIG_ACTIONS[14]->object = &object_0012541C;
	BIG_ACTIONS[15]->object = &object_0012541C;
	BIG_ACTIONS[16]->object = &object_0012541C;
	BIG_ACTIONS[17]->object = &object_0012541C;
	BIG_ACTIONS[18]->object = &object_0012541C;
	BIG_ACTIONS[19]->object = &object_0012541C;
	BIG_ACTIONS[20]->object = &object_0012541C;
	BIG_ACTIONS[21]->object = &object_0012541C;
	BIG_ACTIONS[22]->object = &object_0012541C;
	BIG_ACTIONS[23]->object = &object_0012541C;
	BIG_ACTIONS[24]->object = &object_0012541C;
	BIG_ACTIONS[25]->object = &object_0012541C;
	BIG_ACTIONS[27]->object = &object_0012541C;
	BIG_ACTIONS[28]->object = &object_0012541C;
	BIG_ACTIONS[29]->object = &object_0012541C;
	BIG_ACTIONS[30]->object = &object_0012541C;
	BIG_ACTIONS[31]->object = &object_0012541C;
	BIG_ACTIONS[32]->object = &object_0012541C;
	BIG_ACTIONS[33]->object = &object_0012541C;
	BIG_ACTIONS[34]->object = &object_0012541C;
	BIG_ACTIONS[35]->object = &object_0012541C;
	BIG_ACTIONS[36]->object = &object_0012541C;
	BIG_ACTIONS[37]->object = &object_0012541C;
	BIG_ACTIONS[38]->object = &object_0012541C;
	BIG_ACTIONS[39]->object = &object_0012541C;
	BIG_ACTIONS[40]->object = &object_0012541C;
	BIG_ACTIONS[41]->object = &object_0012541C;
	BIG_ACTIONS[42]->object = &object_0012541C;
	BIG_ACTIONS[43]->object = &object_0012541C;
	BIG_ACTIONS[44]->object = &object_0012541C;
	BIG_ACTIONS[45]->object = &object_0012541C;
	BIG_ACTIONS[46]->object = &object_0012541C;
	BIG_ACTIONS[48]->object = &object_0012541C;
	BIG_ACTIONS[55]->object = &object_0012541C;
	BIG_ACTIONS[56]->object = &object_0012541C;
	BIG_ACTIONS[57]->object = &object_0012541C;
	BIG_ACTIONS[58]->object = &object_0012541C;
	BIG_ACTIONS[59]->object = &object_0012541C;
	BIG_ACTIONS[60]->object = &object_0012541C;
	BIG_ACTIONS[61]->object = &object_0012541C;
	BIG_ACTIONS[62]->object = &object_0012541C;
	BIG_ACTIONS[63]->object = &object_0012541C;
	BIG_ACTIONS[64]->object = &object_0012541C;
	BIG_ACTIONS[65]->object = &object_0012541C;
	BIG_ACTIONS[66]->object = &object_0012541C;
	BIG_ACTIONS[67]->object = &object_0012541C;
	BIG_ACTIONS[68]->object = &object_0012541C;
	BIG_ACTIONS[69]->object = &object_0012541C;
	BIG_ACTIONS[70]->object = &object_0012541C;
	BIG_ACTIONS[72]->object = &object_0012541C;
	BIG_ACTIONS[73]->object = &object_0012541C;
	BIG_ACTIONS[74]->object = &object_0012541C;
	BIG_ACTIONS[75]->object = &object_0012541C;
	BIG_ACTIONS[76]->object = &object_0012541C;
	BIG_ACTIONS[77]->object = &object_0012541C;
	BIG_ACTIONS[78]->object = &object_0012541C;
	BIG_ACTIONS[79]->object = &object_0012541C;
	BIG_ACTIONS[80]->object = &object_0012541C;
	BIG_ACTIONS[81]->object = &object_0012541C;
	BIG_ACTIONS[82]->object = &object_0012541C;
	BIG_ACTIONS[86]->object = &object_0012541C;
	BIG_ACTIONS[87]->object = &object_0012541C;
	BIG_ACTIONS[88]->object = &object_0012541C;
	BIG_ACTIONS[89]->object = &object_0012541C;
	BIG_MODELS[0] = &attach_0011D41C;
	BIG_MODELS[1] = &attach_00126D14;
	BIG_MODELS[2] = &attach_0011F358;
	BIG_MODELS[3] = &attach_001291A8;
	BIG_MOTIONS[0] = &BigEV_Motion;
	WriteJump((void*)0x007CE860, InitBigWeldInfo_mod);
}

void Init_Tikal()
{
	WriteData((NJS_OBJECT**)0x008CEBF8, &object_000038CC); //Left Palm
	WriteData((NJS_OBJECT**)0x008CE084, &object_000036C0); //Left Thumb
	WriteData((NJS_OBJECT**)0x008CEB5C, &object_00003BD8); //Left Fingers
	WriteData((NJS_OBJECT**)0x008CD210, &object_00002850); //Right Palm
	WriteData((NJS_OBJECT**)0x008CC684, &object_00002644); //Right Thumb
	WriteData((NJS_OBJECT**)0x008CD174, &object_00002B38); //Right Fingers
	TikalWeldInfo[0].ModelA = &object_000038CC;
	TikalWeldInfo[0].ModelB = &object_00003BD8;
	TikalWeldInfo[0].VertexPairCount = 4;
	TikalWeldInfo[0].VertIndexes = (unsigned short *)&Tikal_LeftHandIndices_DC;
	TikalWeldInfo[1].ModelA = &object_00002850;
	TikalWeldInfo[1].ModelB = &object_00002B38;
	TikalWeldInfo[1].VertexPairCount = 4;
	TikalWeldInfo[1].VertIndexes = (unsigned short *)&Tikal_RightHandIndices_DC;
}

void Init_Eggman()
{
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
	WriteData((NJS_OBJECT**)0x02D03974, &Eggman_Object);
	WriteData((NJS_OBJECT**)0x02D06F6C, &Eggman_Object);
	WriteData((NJS_OBJECT**)0x02D08DF4, &Eggman_Object);
	WriteData((NJS_OBJECT**)0x02D0AC0C, &Eggman_Object);
	WriteData((NJS_OBJECT**)0x02D64FBC, &Eggman_Object);
	WriteData((NJS_OBJECT**)0x02F9470C, &Eggman_Object);
	WriteData((NJS_OBJECT**)0x02FDF18C, &Eggman_Object);
	WriteData((NJS_OBJECT**)0x0303D284, &Eggman_Object);
	WriteData((NJS_OBJECT**)0x0303EE9C, &Eggman_Object);
	WriteData((NJS_OBJECT**)0x03041A44, &Eggman_Object);
	WriteData((NJS_OBJECT**)0x0304E9AC, &Eggman_Object);
	WriteData((NJS_OBJECT**)0x030C3AD4, &Eggman_Object);
	WriteData((NJS_OBJECT**)0x030C62BC, &Eggman_Object);
	WriteData((NJS_OBJECT**)0x030C7E34, &Eggman_Object);
	WriteData((NJS_OBJECT**)0x03136234, &Eggman_Object);
	WriteData((NJS_OBJECT**)0x0313EB3C, &Eggman_Object);
	WriteData((NJS_OBJECT**)0x03141254, &Eggman_Object);
	WriteData((NJS_OBJECT**)0x03142C4C, &Eggman_Object);
	WriteData((WeldInfo**)0x007B4FBF, (WeldInfo*)&EggmanWeldList_DC);


	//Eggman in Eggmobile for cutscenes (EV_EGGMOBLE0)
	WriteData((NJS_OBJECT**)0x2CD393C, &Eggmobile0_Object);
	WriteData((NJS_OBJECT**)0x2CD46F4, &Eggmobile0_Object);
	WriteData((NJS_OBJECT**)0x2CD594C, &Eggmobile0_Object);
	WriteData((NJS_OBJECT**)0x2CD6904, &Eggmobile0_Object);
	WriteData((NJS_OBJECT**)0x2D41A34, &Eggmobile0_Object);
	WriteData((NJS_OBJECT**)0x2D42BBC, &Eggmobile0_Object);
	WriteData((NJS_OBJECT**)0x2D44434, &Eggmobile0_Object);
	WriteData((NJS_OBJECT**)0x2DCDB14, &Eggmobile0_Object);
	WriteData((NJS_OBJECT**)0x2E2C844, &Eggmobile0_Object);
	WriteData((NJS_OBJECT**)0x2EEC334, &Eggmobile0_Object);
	WriteData((NJS_OBJECT**)0x3018C44, &Eggmobile0_Object);
	WriteData((NJS_OBJECT**)0x3019E5C, &Eggmobile0_Object);
	WriteData((NJS_OBJECT**)0x301B074, &Eggmobile0_Object);
	WriteData((NJS_OBJECT**)0x301C41C, &Eggmobile0_Object);
	WriteData((NJS_OBJECT**)0x301DE94, &Eggmobile0_Object);
	WriteData((NJS_OBJECT**)0x302015C, &Eggmobile0_Object);
	WriteData((NJS_OBJECT**)0x3021854, &Eggmobile0_Object);
	WriteData((NJS_OBJECT**)0x30220EC, &Eggmobile0_Object);
	WriteData((NJS_OBJECT**)0x321A55C, &Eggmobile0_Object);
	WriteData((WeldInfo**)0x006F08FB, (WeldInfo*)&Eggmobile0WeldList_DC);
}

void Init_Metal()
{
	SONIC_OBJECTS[68] = &object_00591068;
	SONIC_OBJECTS[69] = &object_0059C234;
	SONIC_OBJECTS[70] = &object_0059E254;
	WriteJump((void*)0x7D18F0, InitMetalSonicWeldInfo_Fix);
	WriteCall((void*)0x491701, PlaySonicIdleVoice_r);
}

extern "C"
{
	__declspec(dllexport) ModInfo SADXModInfo = { ModLoaderVer };

	__declspec(dllexport) void __cdecl Init(const char *path, const HelperFunctions &helperFunctions)
	{
		if (helperFunctions.Version < 6) {
			PrintDebug("Hey you need to update or something\n");
		};
		HMODULE adv02dll = GetModuleHandle(L"ADV02MODELS");
		HMODULE adv03dll = GetModuleHandle(L"ADV03MODELS");


		//Ini Configuration
		const IniFile *config = new IniFile(std::string(path) + "\\config.ini");
		EnableSonic = config->getBool("Characters", "EnableSonic", true);
		EnableMiles = config->getBool("Characters", "EnableMiles", true);
		EnableKnuckles = config->getBool("Characters", "EnableKnuckles", true);
		EnableAmy = config->getBool("Characters", "EnableAmy", true);
		EnableBig = config->getBool("Characters", "EnableBig", true);
		EnableGamma = config->getBool("Characters", "EnableGamma", true);
		EnableTikal = config->getBool("Characters", "EnableTikal", true);
		EnableEggman = config->getBool("Characters", "EnableEggman", true);
		EnableCDMetalSonic = config->getBool("Characters", "EnableCDMetalSonic", true);
		EnableSkychase = config->getBool("Characters", "EnableSkychase", true);

		DisableSaturnSkyChase = config->getBool("Extras", "DisableSaturnSkyChase", false);
		EnableExtras = config->getBool("Extras", "EnableExtras", false);
		std::string MSHover_String = "Normal";
		MSHover_String = config->getString("Extras", "MetalSonicHoverBehavior", "Normal");
		std::string StretchyShoes_String = "Regular";
		StretchyShoes_String = config->getString("Extras", "StretchyShoes", "Regular");
		if (MSHover_String == "Normal") MSHover = Normal;
		if (MSHover_String == "Swap") MSHover = Swap;
		if (MSHover_String == "Always") MSHover = Always;
		if (StretchyShoes_String == "Regular") StretchyShoes = Regular;
		if (StretchyShoes_String == "LSShoeMorphs") StretchyShoes = LSShoeMorphs;
		if (StretchyShoes_String == "Disable") StretchyShoes = Disable;
		delete config;

		//Functions
		if (EnableSonic && StretchyShoes == LSShoeMorphs)
		{
			WriteJump((void*)0x00493500, Sonic_MorphStretchyFeet_asm);
		}
		if (EnableSonic && StretchyShoes == Disable)
		{
			WriteData((char*)0x00493500, (char)0xC3);
		}
		WriteData<2>((void*)0x004916A5, 0x90u);
		if (MSHover == Swap)
		{
			WriteJump((void*)0x00495BE0, Sonic_Run2Ani_swap);
			WriteJump((void*)0x00495B00, Sonic_Run1Ani_swap);
		}
		if (MSHover == Always)
		{
			WriteJump((void*)0x00495BE0, Sonic_Run2Ani_swap);
			WriteJump((void*)0x00495B00, Sonic_Run1Ani_origasm);
		}

		//Sonic
		if (EnableSonic)
		{
			Init_Sonic();
			//ResizeTextureList((NJS_TEXLIST*)0x0142272C, 80);
			ReplacePVM("SONIC", "SONIC_DC");
			ReplacePVM("SON_EFF", "SON_EFF_DC");
			ReplacePVM("SUPERSONIC", "SUPERSONIC_DC");
		}

		if (EnableCDMetalSonic)
		{
			Init_Metal();
			ReplacePVM("METALSONIC", "METALSONIC_DC");
		}

		//Tails
		if (EnableMiles)
		{
			Init_Miles();
			NJS_OBJECT **___ADV03_OBJECTS = (NJS_OBJECT **)GetProcAddress(adv03dll, "___ADV03_OBJECTS");
			___ADV03_OBJECTS[31] = &WarriorFeather_Upgrade;
			ReplacePVM("MILES", "MILES_DC");
			ReplacePVM("M_HEAD_1", "M_HEAD_1_DC");
			ReplacePVM("M_TR_P", "M_TR_P_DC");
		}

		//Knuckles
		if (EnableKnuckles)
		{
			Init_Knux();
			NJS_OBJECT **___ADV02_OBJECTS = (NJS_OBJECT **)GetProcAddress(adv02dll, "___ADV02_OBJECTS");
			___ADV02_OBJECTS[116] = &FightGloves_Upgrade;
			___ADV02_OBJECTS[117] = &ShovelClaw_Upgrade;
			ReplacePVM("KNUCKLES", "KNUCKLES_DC");
			ReplacePVM("KNU_EFF", "KNU_EFF_DC");
		}

		//Amy
		if (EnableAmy)
		{
			Init_Amy();
			ReplacePVM("AMY", "AMY_DC");
			ReplacePVM("A_HEAD", "A_HEAD_DC");
			ReplacePVM("AMY_EFF", "AMY_EFF_DC");
			ReplacePVM("AMY_EGGROBO", "AMY_EGGROBO_DC");
			ReplacePVM("AMYROB_WING", "AMYROB_WING_DC");
		}

		//Big
		if (EnableBig)
		{
			Init_Big();
			ReplacePVM("BIG", "BIG_DC");
		}

		//Gamma
		if (EnableGamma)
		{
			materials_00200D48[7]->attrflags |= NJD_FLAG_IGNORE_LIGHT;
			materials_002009C0[2]->attrflags |= NJD_FLAG_IGNORE_LIGHT;
			materials_0020052C[1]->attrflags |= NJD_FLAG_IGNORE_LIGHT;
			materials_0020052C[2]->attrflags |= NJD_FLAG_IGNORE_LIGHT;
			materials_00204EC8[2]->attrflags |= NJD_FLAG_IGNORE_LIGHT;
			materials_002062D8[3]->attrflags |= NJD_FLAG_IGNORE_LIGHT;
			materials_0020B9B8[3]->attrflags |= NJD_FLAG_IGNORE_LIGHT;
		}

		//Tikal
		if (EnableTikal)
		{
			Init_Tikal();
			ReplacePVM("TIKAL", "TIKAL_DC");
		}

		//Eggman
		if (EnableEggman)
		{
			Init_Eggman();
			ReplacePVM("EGGMAN", "EGGMAN_DC");
			ReplacePVM("EV_EGGMOBLE0", "EV_EGGMOBLE0_DC");
		}

		//Sky Chase
		if (EnableSkychase)
		{
			if (DisableSaturnSkyChase)
			{
				WriteData((NJS_OBJECT**)0x0028B7A0C, &Tornado1_Object);
				WriteData((NJS_OBJECT**)0x0028BA71C, &Tornado1_Object);
				WriteData((NJS_OBJECT**)0x0028BDDBC, &Tornado1_Object);
				WriteData((NJS_OBJECT**)0x0028C09FC, &Tornado1_Object);
				WriteData((NJS_OBJECT**)0x0027EFDDC, &Tornado2Before_Object);
				WriteData((NJS_OBJECT**)0x0027F2AA4, &Tornado2Before_Object);
				WriteData((NJS_OBJECT**)0x0027F612C, &Tornado2Before_Object);
				WriteData((NJS_OBJECT**)0x0027F8974, &Tornado2Before_Object);
				WriteData((NJS_OBJECT**)0x00280F23C, &Tornado2Change_Object);
				WriteData((NJS_OBJECT**)0x002811CE4, &Tornado2Change_Object);
				WriteData((NJS_OBJECT**)0x002814D9C, &Tornado2Change_Object);
				WriteData((NJS_OBJECT**)0x002817514, &Tornado2Change_Object);
			}
			else
			{
				WriteData((NJS_OBJECT**)0x0028B7A0C, &Tornado1_Saturn);
				WriteData((NJS_OBJECT**)0x0028BA71C, &Tornado1_Saturn);
				WriteData((NJS_OBJECT**)0x0028BDDBC, &Tornado1_Saturn);
				WriteData((NJS_OBJECT**)0x0028C09FC, &Tornado1_Saturn);
				WriteData((NJS_OBJECT**)0x0027EFDDC, &Tornado2Before_Saturn);
				WriteData((NJS_OBJECT**)0x0027F2AA4, &Tornado2Before_Saturn);
				WriteData((NJS_OBJECT**)0x0027F612C, &Tornado2Before_Saturn);
				WriteData((NJS_OBJECT**)0x0027F8974, &Tornado2Before_Saturn);
				WriteData((NJS_OBJECT**)0x00280F23C, &Tornado2Change_Saturn);
				WriteData((NJS_OBJECT**)0x002811CE4, &Tornado2Change_Saturn);
				WriteData((NJS_OBJECT**)0x002814D9C, &Tornado2Change_Saturn);
				WriteData((NJS_OBJECT**)0x002817514, &Tornado2Change_Saturn);
			}
			WriteData((NJS_OBJECT**)0x002935DFC, &TornadoDestroyed_Object);
			WriteData((NJS_OBJECT**)0x0028988FC, &Tornado2Transformation_Object);
			WriteData((NJS_OBJECT**)0x028E2C88, &object_0009153C); //Beam in Act 1
			WriteData((NJS_OBJECT**)0x28E596C, &object_0009153C); //Beam in Act 1
			WriteData((char*)0x0062751B, 0x00, 1); //Force Tornado light type
			WriteData((char*)0x0062AC1F, 0x00, 1); //Force Tornado light type (transformation cutscene)
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
			WriteData((NJS_OBJECT**)0x032ECE0C, &EV_TR2CHANGE_Object);
			ReplacePVM("SHOOTING1", "SHOOTING1_DC");
			ReplacePVM("SHOOTING2", "SHOOTING2_DC");
			ReplacePVM("EV_TR1_WITH_SONIC", "EV_TR1_WITH_SONIC_DC");
			ReplacePVM("EV_TR2BEFORE_WITH_SONIC", "EV_TR2BEFORE_WITH_SONIC_DC");
			ReplacePVM("EV_TR2CHANGE_WITH_SONIC", "EV_TR2CHANGE_WITH_SONIC_DC");

			//Lantern API Export
			HMODULE Lantern = GetModuleHandle(L"sadx-dc-lighting");
			if (Lantern != nullptr)
			{
				material_register(Specular0, LengthOfArray(Specular0), &ForceDiffuse0Specular0);
				material_register(Specular1, LengthOfArray(Specular1), &ForceDiffuse0Specular1);
				material_register(Specular2, LengthOfArray(Specular2), &ForceDiffuse2Specular2);
				material_register(Specular3, LengthOfArray(Specular3), &ForceDiffuse2Specular3);
				material_register(TailsBody, LengthOfArray(TailsBody), &ForceDiffuse0Specular0_Tails);
				material_register(TailsShoes, LengthOfArray(TailsShoes), &ForceDiffuse0Specular1_Tails);
				if (EnableSonic)
				{
					ForceDiffuse2Specular2_Object(&object_0062FE6C); //Super Sonic jumpball
					if (EnableExtras)
					{
						ForceDiffuse2Specular2_Object(&object_LShoeSpin); //Sonic jumpball with LS shoes
						ForceDiffuse2Specular2_Object(&object_SShoeHeelL); //Super Sonic Left Heel
						ForceDiffuse2Specular2_Object(&object_SShoeToeL); //Super Sonic Left Toe
						ForceDiffuse2Specular2_Object(&object_SShoeHeelR); //Super Sonic Right Heel
						ForceDiffuse2Specular2_Object(&object_SShoeToeR); //Super Sonic Right Toe
						ForceDiffuse2Specular2_Object(&object_SSCrystalRing); //Super Sonic arm with Crystal Ring
					}
				}
			}
		}
	}

	__declspec(dllexport) void __cdecl OnFrame()
	{
		//Big's rod upgrade lighting - basically make it ignore specular when it's part of Big's model (upgrade attained), otherwise don't (field model)
		if (BigRodIgnoresSpecular && !(BIG_OBJECTS[19]->child->basicdxmodel->mats[0].attrflags & NJD_FLAG_IGNORE_SPECULAR)) ForceIgnoreSpecular_Object(BIG_OBJECTS[19]->child, true);
		if (!BigRodIgnoresSpecular && BIG_OBJECTS[19]->child->basicdxmodel->mats[0].attrflags & NJD_FLAG_IGNORE_SPECULAR) ForceSpecular_Object(BIG_OBJECTS[19]->child, true);
		if (EventFlagArray[EventFlags_Big_PowerRod] == 1) BigRodIgnoresSpecular = true; else BigRodIgnoresSpecular = false;
		//Consistency additions
		if (EnableExtras)
		{
			//Sonic OnFrame Checks
			if (EnableSonic)
			{
				if (SONIC_OBJECTS[19]->sibling == SONIC_OBJECTS[58]) //LSShoe Check for Jumpball
				{
					SONIC_OBJECTS[66] = &object_LShoeSpin;
					SONIC_ACTIONS[14]->object = &object_LShoeSpin;
					attach_0057BC18.mats->attr_texId = 28;
					attach_0062FE40.mats->attr_texId = 79;
				}
				else
				{
					SONIC_OBJECTS[66] = &object_005729CC;
					SONIC_ACTIONS[14]->object = &object_005729CC;
					attach_0057BC18.mats->attr_texId = 18;
					attach_0062FE40.mats->attr_texId = 15;
				}
				if (EntityData1Ptrs[0])
				{
					if (SONIC_OBJECTS[19]->sibling != SONIC_OBJECTS[58]) //Shoe check for Super Sonic
					{
						SONIC_OBJECTS[41]->model = object_SShoeHeelL.model; //Super Sonic Left Heel
						SONIC_OBJECTS[42]->model = object_SShoeToeL.model; //Super Sonic Left Toe
						SONIC_OBJECTS[36]->model = object_SShoeHeelR.model; //Super Sonic Right Heel
						SONIC_OBJECTS[37]->model = object_SShoeToeR.model; //Super Sonic Right Toe
					}
					else
					{
						SONIC_OBJECTS[41]->model = object_00622970.model; //Super Sonic Left Heel
						SONIC_OBJECTS[42]->model = object_00622254.model; //Super Sonic Left Toe
						SONIC_OBJECTS[36]->model = object_00624308.model; //Super Sonic Right Heel
						SONIC_OBJECTS[37]->model = object_00623C14.model; //Super Sonic Right Toe
					}
				}
				if (SONIC_OBJECTS[62]->sibling == SONIC_OBJECTS[63])
				{
					SONIC_OBJECTS[25]->model = object_SSCrystalRing.model;
					SonicWeldInfo[23].VertIndexes = SS_CrystalRingIndices_DC;
				}
				else
				{
					SONIC_OBJECTS[25]->model = object_0062840C.model;
					SonicWeldInfo[23].VertIndexes = Sonic_LowerArmIndices_DC;
				}
			}
			//Miles OnFrame Checks
			if (EnableMiles)
			{
				if (MILES_OBJECTS[28]->sibling == MILES_OBJECTS[65])
				{
					object_00439824.model = object_0046EE44.model;
					object_0043A634.model = object_0046FC84.model;
					attach_00441460.mats->attr_texId = 24;
				}
				else
				{
					object_00439824.model = &attach_004397F8;
					object_0043A634.model = &attach_0043A608;
					attach_00441460.mats->attr_texId = 14;
				}
			}
			//Knuckles OnFrame Checks
			if (EnableKnuckles)
			{
				if (KNUCKLES_OBJECTS[60]->model == KNUCKLES_MODELS[17]) //Fighting Gloves Check
				{
					object_002F70C0.model = KNUCKLES_MODELS[15]; //Left Wrist
					object_002F6C70.model = KNUCKLES_MODELS[16]; //Left Hand
					object_002F6A98.model = KNUCKLES_MODELS[17]; //Left Fingers
					object_002F6634.model = KNUCKLES_MODELS[18]; //Left Thumb
					object_002F81F0.model = KNUCKLES_MODELS[19]; //Right Wrist
					object_002F7DB8.model = KNUCKLES_MODELS[20]; //Right Hand
					object_002F7BE8.model = KNUCKLES_MODELS[21]; //Right Fingers
					object_002F7774.model = KNUCKLES_MODELS[22]; //Right Thumb
					attach_002F0DF8.mats->attr_texId = 22; //Replaced texture
				}
				else if (KNUCKLES_OBJECTS[60]->model == KNUCKLES_MODELS[0]) //Shovel Claw Check
				{
					object_002F70C0.model = &attach_002F7094; //Left Wrist (original)
					object_002F6C70.model = &attach_002F6C44; //Left Hand (original)
					object_002F6634.model = &attach_002F6608; //Left Thumb (original)
					object_002F6A98.model = KNUCKLES_MODELS[0]; //Left Fingers (replaced)
					object_002F81F0.model = &attach_002F81C4; //Right Wrist (original)
					object_002F7DB8.model = &attach_002F7D8C; //Right Hand (original)
					object_002F7BE8.model = KNUCKLES_MODELS[2]; //Right Fingers (replaced)
					object_002F7774.model = &attach_002F7748; //Right Thumb (original)
					attach_002F0DF8.mats->attr_texId = 9; //Original texture
				}
				else if (KNUCKLES_OBJECTS[60]->model == KNUCKLES_MODELS[1]) //Fighting Claws Check
				{
					object_002F70C0.model = KNUCKLES_MODELS[15]; //Left Wrist
					object_002F6C70.model = KNUCKLES_MODELS[16]; //Left Hand
					object_002F6A98.model = KNUCKLES_MODELS[1]; //Left Fingers
					object_002F6634.model = KNUCKLES_MODELS[18]; //Left Thumb
					object_002F81F0.model = KNUCKLES_MODELS[19]; //Right Wrist
					object_002F7DB8.model = KNUCKLES_MODELS[20]; //Right Hand
					object_002F7BE8.model = KNUCKLES_MODELS[3]; //Right Fingers
					object_002F7774.model = KNUCKLES_MODELS[21]; //Right Thumb
					attach_002F0DF8.mats->attr_texId = 22; //Replaced texture
				}
				else
				{
					object_002F70C0.model = &attach_002F7094; //Left Wrist (original)
					object_002F6C70.model = &attach_002F6C44; //Left Hand (original)
					object_002F6A98.model = &attach_002F6A6C; //Left Fingers (original)
					object_002F6634.model = &attach_002F6608; //Left Thumb (original)
					object_002F81F0.model = &attach_002F81C4; //Right Wrist (original)
					object_002F7DB8.model = &attach_002F7D8C; //Right Hand (original)
					object_002F7BE8.model = &attach_002F7BBC; //Right Fingers (original)
					object_002F7774.model = &attach_002F7748; //Right Thumb (original)
					attach_002F0DF8.mats->attr_texId = 9; //Original texture
				}
			}
		}
	}
}