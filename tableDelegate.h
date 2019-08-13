#pragma once
#include <QStyledItemDelegate>
#include <qitemdelegate.h>
#include <QLineEdit>

class TableDelegate : public QStyledItemDelegate
{
public:
	QWidget* createEditor(QWidget *parent, const QStyleOptionViewItem & option,
		const QModelIndex & index) const
	{
		QLineEdit *lineEdit = new QLineEdit(parent);
		// Set validator
		QDoubleValidator *validator = new QDoubleValidator(lineEdit);
		lineEdit->setValidator(validator);
		return lineEdit;
	}
};
