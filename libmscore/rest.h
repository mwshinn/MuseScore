//=============================================================================
//  MuseScore
//  Music Composition & Notation
//
//  Copyright (C) 2002-2011 Werner Schweer
//
//  This program is free software; you can redistribute it and/or modify
//  it under the terms of the GNU General Public License version 2
//  as published by the Free Software Foundation and appearing in
//  the file LICENCE.GPL
//=============================================================================

#ifndef __REST_H__
#define __REST_H__

#include "chordrest.h"

namespace Ms {

class TDuration;
enum class SymId : short;

//---------------------------------------------------------
//    @@ Rest
///     This class implements a rest.
//---------------------------------------------------------

class Rest : public ChordRest {
      Q_OBJECT

      // values calculated by layout:
      SymId _sym;
      int dotline;            // depends on rest symbol
      qreal _mmWidth;         // width of multi measure rest

      virtual QRectF drag(EditData*) override;
      virtual qreal upPos()   const override;
      virtual qreal downPos() const override;
      virtual qreal centerX() const override;
      virtual void setUserOff(const QPointF& o) override;

   public:
      Rest(Score* s = 0);
      Rest(Score*, const TDuration&);
      virtual Rest* clone() const override      { return new Rest(*this); }
      virtual ElementType type() const override { return ElementType::REST; }

      virtual Measure* measure() const override { return parent() ? (Measure*)(parent()->parent()) : 0; }
      virtual qreal mag() const override;
      virtual void draw(QPainter*) const override;
      virtual void scanElements(void* data, void (*func)(void*, Element*), bool all=true) override;

      virtual bool acceptDrop(MuseScoreView*, const QPointF&, Element*) const override;
      virtual Element* drop(const DropData&) override;
      virtual void layout() override;

      virtual void reset() override;

      void setMMWidth(qreal val);
      qreal mmWidth() const        { return _mmWidth; }
      SymId getSymbol(TDuration::DurationType type, int line, int lines,  int* yoffset);

      int getDotline() const { return dotline; }
      SymId sym() const        { return _sym;    }
      int computeLineOffset();
      bool isFullMeasureRest() const { return durationType() == TDuration::DurationType::V_MEASURE; }

      virtual int upLine() const;
      virtual int downLine() const;
      virtual QPointF stemPos() const;
      virtual qreal stemPosX() const;
      virtual QPointF stemPosBeam() const;
      };


}     // namespace Ms
#endif

