#pragma once
#include <memory>
#include <vector>
#include <map>
#include <string>

namespace QuestCore
{
	class IParagraph;
	class Item;
	class Inventory;
	class ICaseContainer;
	class ITextViewFactory;
	class IButtonPanelFactory;

	struct Node
	{
	private:
		using ParagraphPtr = std::shared_ptr<IParagraph>;
		using CaseContainerPtr = std::shared_ptr<ICaseContainer>;

	public:
		ParagraphPtr paragraph;
		CaseContainerPtr caseContainer;
	};

	class QuestBase
	{
	protected:
		using ItemPtr = std::shared_ptr<Item>;
		using InventoryPtr = std::shared_ptr<Inventory>;
		using TextViewFactoryPtr = std::shared_ptr<ITextViewFactory>;
		using ButtonsFactoryPtr = std::shared_ptr<IButtonPanelFactory>;

	public:
		using Ptr = std::shared_ptr<QuestBase>;

		QuestBase(const TextViewFactoryPtr& viewFactory, const ButtonsFactoryPtr& buttonsFactory);
		virtual ~QuestBase() = default;

		virtual void Update();
		virtual const std::map<std::string, InventoryPtr>& GetInventories() const = 0;

	protected:
		virtual const std::map<std::string, Node>& GetRoots() const = 0;

	private:
		TextViewFactoryPtr _viewFactory;
		ButtonsFactoryPtr _buttonsFactory;
	};
};
