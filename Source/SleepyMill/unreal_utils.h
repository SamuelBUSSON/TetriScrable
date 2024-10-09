#pragma once

namespace unreal_utils
{
	template<typename T>
	T pick_random(TArray<T> array)
	{
		check(array.Num() > 0);
		
		return array[FMath::RandRange(0, array.Num() - 1)];
	}
};
