



sint32 MAP_s32MapThisValue(sint32 Copy_s32Value, sint32 Copy_s32InputMin, sint32 Copy_s32InputMax, sint32 Copy_s32OutputMin, sint32 Copy_s32OutputMax)
{
	sint32 Local_s32MappedValue;
	
	
	Local_s32MappedValue = (Copy_s32Value - Copy_s32InputMin) * (Copy_s32OutputMax - Copy_s32OutputMin) / (Copy_s32InputMax - Copy_s32InputMin) + Copy_s32OutputMin;
	
	
	return Local_s32MappedValue;
}
