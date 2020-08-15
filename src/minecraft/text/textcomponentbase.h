#ifndef TEXTCOMPONENTBASE_H
#define TEXTCOMPONENTBASE_H

#include <qiterator.h>

#include "textcomponent.h"

class TextComponentBase : public TextComponent {
 public:
  TextComponentBase();
  TextComponent *AppendSibling(TextComponent *text) override;
  QList<TextComponent *> GetSiblings() const override;
  TextComponent *AppendText(const QString &text) override;

  void SetStyle(Style style) override;
  Style &GetStyle() override;

  QString GetUnformattedText() override;
  QString GetFormattedText() override;

 protected:
  QList<TextComponent *> siblings_;

 private:
  Style style_;
};

#endif  // TEXTCOMPONENTBASE_H
