#pragma once

template<typename ElementType>
class TFMPriorityList
{
public:
	ElementType Element;
	TFMPriorityList<ElementType>* Next;

	explicit TFMPriorityList(const ElementType& InElement, TList<ElementType>* InNext = nullptr)
	{
		Element = InElement;
		Next = InNext;
	}

	
};
