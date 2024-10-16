#pragma once

template<typename NodeType, typename ElementType>
class TFMPriorityListIterator
{	
public:
	explicit TFMPriorityListIterator(NodeType* StartNode)
		: CurrentNode(StartNode)
	{
	}

// Accessors
public:
	ElementType& operator*() const
	{
		return CurrentNode->GetValue();
	}

	ElementType& operator->() const
	{
		return CurrentNode->GetValue();
	}

	NodeType* GetNode() const
	{
		return CurrentNode;
	}

// Increment Operator
public:
	TFMPriorityListIterator& operator++()
	{
		CurrentNode = CurrentNode->GetNextNode();
		return *this;
	}

	TFMPriorityListIterator operator++(int)
	{
		TFMPriorityListIterator Result = *this;
		++(*this);
		return Result;
	}

// Compare Operator
public:
	explicit operator bool() const
	{
		return CurrentNode != nullptr;
	}

	bool operator==(const TFMPriorityListIterator& Right)
	{
		return CurrentNode == Right.CurrentNode;
	}

	bool operator!=(const TFMPriorityListIterator& Right)
	{
		return CurrentNode != Right.CurrentNode;
	}

private:
	NodeType* CurrentNode;
};


template<typename ElementType>
class TFMPriorityList
{
public:
	class TFMPriorityListNode
	{
	public:
		friend class TFMPriorityList;
		
		explicit TFMPriorityListNode(const ElementType& InValue)
			: Value(InValue), NextNode(nullptr)
		{
		}

	public:
		const ElementType& GetValue() const
		{
			return Value;
		}

		ElementType& GetValue()
		{
			return Value;
		}

		const TFMPriorityListNode* GetNextNode() const
		{
			return NextNode;
		}

		TFMPriorityListNode* GetNextNode()
		{
			return NextNode;
		}
	
	private:
		ElementType Value;
		TFMPriorityListNode* NextNode;
	};

public:
	// Node
	using TNode = TFMPriorityListNode;
	using TNodePtr = TNode*;

	// Iterator
	using TIterator = TFMPriorityListIterator<TNode, ElementType>;
	using TConstIterator = TFMPriorityListIterator<TNode, const ElementType>;

// Iterator begin(), end()
public:
	TIterator begin() { return TIterator(Head); }
	TIterator begin() const { return TIterator(Head); }
	TIterator end() { return TIterator(nullptr); }
	TIterator end() const { return TIterator(nullptr); }
	
public:
	TFMPriorityList()
		: Head(nullptr), ListSize(0)
	{
	}

	virtual ~TFMPriorityList()
	{
		Empty();
	}

	void InsertNode(const ElementType& InElement)
	{
		TNodePtr NewNode = new TNode(InElement);

		// Add Node
		if (Head == nullptr)
		{
			Head = NewNode;
		}
		else if (NewNode->GetValue() < Head->GetValue())	// Add Node To Head
		{
			NewNode->NextNode = Head;
			Head = NewNode;
		}
		else												// Add Node by ASC
		{
			TNodePtr CurrentNode = Head;
			TNodePtr NextNode = Head->GetNextNode();
			while (NextNode != nullptr)
			{
				if (NewNode->GetValue() < NextNode->GetValue())
				{
					break;
				}

				CurrentNode = CurrentNode->GetNextNode();
				NextNode = NextNode->GetNextNode();
			}

			CurrentNode->NextNode = NewNode;
			NewNode->NextNode = NextNode;
		}
		
		ListSize++;
	}

	void PopHead()
	{
		if (Head != nullptr)
		{
			TNodePtr Node = Head->NextNode;
			delete Head;
			Head = Node;
			
			ListSize--;
		}
	}

	void Empty()
	{
		TNodePtr Node;
		while (Head != nullptr)
		{
			Node = Head->NextNode;
			delete Head;
			Head = Node;
		}

		Head = nullptr;
		ListSize = 0;
	}

	TNodePtr GetHead() const
	{
		return Head;
	}

	TNodePtr FindNode(const ElementType& InElement)
	{
		TNodePtr Node = Head;
		while (Node != nullptr)
		{
			if (Node->GetValue() == InElement)
			{
				break;
			}

			Node = Node->NextNode;
		}

		return Node;
	}

	bool Contains(const ElementType& InElement)
	{
		return (FindNode(InElement) != nullptr);
	}

	bool IsEmpty() const
	{
		return ListSize == 0;
	}

	int32 Num() const
	{
		return ListSize;
	}
	
	
private:
	TNodePtr Head;
	int32 ListSize;
};
