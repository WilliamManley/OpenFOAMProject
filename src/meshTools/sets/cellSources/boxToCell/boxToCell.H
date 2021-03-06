/*---------------------------------------------------------------------------*\
  =========                 |
  \\      /  F ield         | OpenFOAM: The Open Source CFD Toolbox
   \\    /   O peration     |
    \\  /    A nd           | www.openfoam.com
     \\/     M anipulation  |
-------------------------------------------------------------------------------
    Copyright (C) 2011-2017 OpenFOAM Foundation
    Copyright (C) 2018 OpenCFD Ltd.
-------------------------------------------------------------------------------
License
    This file is part of OpenFOAM.

    OpenFOAM is free software: you can redistribute it and/or modify it
    under the terms of the GNU General Public License as published by
    the Free Software Foundation, either version 3 of the License, or
    (at your option) any later version.

    OpenFOAM is distributed in the hope that it will be useful, but WITHOUT
    ANY WARRANTY; without even the implied warranty of MERCHANTABILITY or
    FITNESS FOR A PARTICULAR PURPOSE.  See the GNU General Public License
    for more details.

    You should have received a copy of the GNU General Public License
    along with OpenFOAM.  If not, see <http://www.gnu.org/licenses/>.

Class
    Foam::boxToCell

Description
    A topoSetCellSource to select cells based on cell centres inside box(es).

    \heading Dictionary parameters
    \table
        Property    | Description                           | Required | Default
        boxes       | Multiple bounding boxes               | partly   |
        box         | A single bounding box                 | partly   |
        min         | Minimum point for a single box        | partly   |
        max         | Maximum point for a single box        | partly   |
    \endtable

Note
    Must specify "boxes", "box" or a "min/max" pair
    (compatibility with searchable box) - highest to lowest precedence.

SourceFiles
    boxToCell.C

\*---------------------------------------------------------------------------*/

#ifndef boxToCell_H
#define boxToCell_H

#include "topoSetCellSource.H"
#include "treeBoundBoxList.H"

// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

namespace Foam
{

/*---------------------------------------------------------------------------*\
                         Class boxToCell Declaration
\*---------------------------------------------------------------------------*/

class boxToCell
:
    public topoSetCellSource
{
    // Private data

        //- Add usage string
        static addToUsageTable usage_;

        //- Bounding boxes
        treeBoundBoxList bbs_;


    // Private Member Functions

        void combine(topoSet& set, const bool add) const;


public:

    //- Runtime type information
    TypeName("boxToCell");

    // Constructors

        //- Construct from components, copying bounding boxes
        boxToCell(const polyMesh& mesh, const treeBoundBoxList& bbs);

        //- Construct from components, moving bounding boxes
        boxToCell(const polyMesh& mesh, treeBoundBoxList&& bbs);

        //- Construct from dictionary
        boxToCell(const polyMesh& mesh, const dictionary& dict);

        //- Construct from stream - a single box.
        boxToCell(const polyMesh& mesh, Istream& is);


    //- Destructor
    virtual ~boxToCell() = default;


    // Member Functions

        virtual void applyToSet
        (
            const topoSetSource::setAction action,
            topoSet& set
        ) const;
};


// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

} // End namespace Foam

// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

#endif

// ************************************************************************* //
