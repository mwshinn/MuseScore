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

#ifndef __TABLATURE_H__
#define __TABLATURE_H__

#include "xml.h"

namespace Ms {

class Chord;
class Note;

//---------------------------------------------------------
//   StringData
//---------------------------------------------------------

class StringData {
//      QList<int>  stringTable { 40, 45, 50, 55, 59, 64 };   // guitar is default
//      int         _frets = 19;
      QList<int>  stringTable {  };                         // no strings by default
      int         _frets = 0;

      static bool bFretting;

      void sortChordNotes(QMap<int, Note *>& sortedNotes, const Chord* chord, int* count) const;

public:
      StringData() {}
      StringData(int numFrets, int numStrings, int strings[]);
      StringData(int numFrets, QList<int>& strings);
      bool        convertPitch(int pitch, int* string, int* fret) const;
      int         fret(int pitch, int string) const;
      void        fretChords(Chord * chord) const;
      int         getPitch(int string, int fret) const;
      int         strings() const         { return stringTable.size(); }
      QList<int>  stringList() const      { return stringTable; }
      QList<int>&  stringList()           { return stringTable; }
      int         frets() const           { return _frets; }
      void        setFrets(int val)       { _frets = val; }
      void        read(XmlReader&);
      void        write(Xml&) const;
//      void        readMusicXML(XmlReader& de);
      void        writeMusicXML(Xml& xml) const;
      bool operator==(const StringData& d) const { return d._frets == _frets && d.stringTable == stringTable; }
      };

}     // namespace Ms
#endif

