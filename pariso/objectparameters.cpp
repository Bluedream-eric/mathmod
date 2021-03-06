/***************************************************************************
 *   Copyright (C) 2020by Abderrahman Taha                                *
 *                                                                         *
 *                                                                         *
 *   This program is free software; you can redistribute it and/or modify  *
 *   it under the terms of the GNU General Public License as published by  *
 *   the Free Software Foundation; either version 2 of the License, or     *
 *   (at your option) any later version.                                   *
 *                                                                         *
 *   This program is distributed in the hope that it will be useful,       *
 *   but WITHOUT ANY WARRANTY; without even the implied warranty of        *
 *   MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the         *
 *   GNU General Public License for more details.                          *
 *                                                                         *
 *   You should have received a copy of the GNU General Public License     *
 *   along with this program; if not, write to the                         *
 *   Free Software Foundation, Inc.,                                       *
 *   51 Franklin Street, Fifth Floor,Boston, MA 02110-1301 USA             *
 ***************************************************************************/
#include "objectparameters.h"

static float StaticColor[20] =
{
    // Green(Back face)
    0.3f, 0.5f, 0.0f, 1.0f,
    // Gold (Front face)
    249.0f / 255.0f, 170.0f / 255.0f, 0.0f, 1.0f,
    // grid:
    0.1f, 0.3f, 0.1f, 0.5f,
    // Background:
    0.0f, 0.0f, 0.0f, 1.0f,
    // Condition:
    1.0f, 0.2f, 0.0f, 1.0f
}; // greencol, goldcol,...

MasterThread::MasterThread() {}
MasterThread::~MasterThread() {}
WorkerThread::WorkerThread() {}
WorkerThread::~WorkerThread() {}
ParisoObject::ParisoObject() {}
ParisoObject::~ParisoObject() {}
///+++++++++++++++++++++++++++++++++++++++++
uint ParisoObject::CNDtoUse(uint index, struct ComponentInfos *components)
{
    uint idx = 0;
    for (uint i = 0; i < components->NbComponents.size() - 1; i++)
        idx += components->NbComponents[i];
    for (uint fctnb = 0;
            fctnb < (components->NbComponents[components->NbComponents.size() - 1]);
            fctnb++)
        if (index <= components->ParisoVertex[2 * (fctnb + idx) + 1] &&
                index >= components->ParisoVertex[2 * (fctnb + idx)])
            return fctnb;
    return 30;
}

//+++++++++++++++++++++++++++++++++++++++++
void ParisoObject::clear(struct ComponentInfos *cp)
{
    cp->ParisoTriangle.clear();
    cp->ParisoVertex.clear();
    cp->NbComponents.clear();
    cp->ThereisCND.clear();
    cp->ParisoCondition.clear();
    cp->ThereisRGBA.clear();

    cp->NbTrianglesVerifyCND.clear();
    cp->NbTrianglesNoCND.clear();
    cp->NbTrianglesNotVerifyCND.clear();
    cp->NbTrianglesBorderCND.clear();

    cp->ParisoCurrentComponentIndex = 0;
    cp->ParisoNbComponents = 0;
    cp->Interleave = true;
    cp->pariso = false;
    cp->updateviewer = false;
}

ObjectParameters::ObjectParameters()
{
    objectproperties.VertxNumber = objectproperties.PolyNumber =
                                       objectproperties.NbPolygnNbVertexPtMin = 0;
    objectproperties.RotStrength = 0;
    objectproperties.zminim = -350.0;
    objectproperties.polyfactor = 1.0;
    objectproperties.polyunits = 1.0;
    objectproperties.ScalCoeff = 1.0;
    objectproperties.view_rotx = 90.0;
    objectproperties.view_roty = 90.0;
    objectproperties.view_rotz = 1.0;
    objectproperties.IndexCurrentFormula = -1;

    objectproperties.frontcols = new float[40];
    objectproperties.backcols = new float[40];

    objectproperties.gridcol[0] = StaticColor[8];
    objectproperties.gridcol[1] = StaticColor[9];
    objectproperties.gridcol[2] = StaticColor[10];
    objectproperties.gridcol[3] = .5;
    objectproperties.groundcol[0] = StaticColor[12];
    objectproperties.groundcol[1] = StaticColor[13];
    objectproperties.groundcol[2] = StaticColor[14];
    objectproperties.groundcol[3] = 1.0;

    objectproperties.backcol[0] = objectproperties.backcols[0] = 0.2f;
    objectproperties.backcol[1] = objectproperties.backcols[1] = 0.8f;
    objectproperties.backcol[2] = objectproperties.backcols[2] = 0.1f;
    objectproperties.backcol[3] = objectproperties.backcols[3] = 1.0f;

    objectproperties.backcols[1 * 4 + 0] = 0.6f;
    objectproperties.backcols[1 * 4 + 1] = 0.6f;
    objectproperties.backcols[1 * 4 + 2] = 0.9f;
    objectproperties.backcols[1 * 4 + 3] = 1.0f;

    objectproperties.backcols[2 * 4 + 0] = 0.8f;
    objectproperties.backcols[2 * 4 + 1] = 0.6f;
    objectproperties.backcols[2 * 4 + 2] = 0.3f;
    objectproperties.backcols[2 * 4 + 3] = 1.0f;

    objectproperties.backcols[3 * 4 + 0] = 0.9f;
    objectproperties.backcols[3 * 4 + 1] = 0.8f;
    objectproperties.backcols[3 * 4 + 2] = 0.6f;
    objectproperties.backcols[3 * 4 + 3] = 1.0f;

    objectproperties.backcols[4 * 4 + 0] = 0.93f;
    objectproperties.backcols[4 * 4 + 1] = 0.2f;
    objectproperties.backcols[4 * 4 + 2] = 0.1f;
    objectproperties.backcols[4 * 4 + 3] = 1.0f;

    objectproperties.backcols[5 * 4 + 0] = 0.3f;
    objectproperties.backcols[5 * 4 + 1] = 0.72f;
    objectproperties.backcols[5 * 4 + 2] = 0.63f;
    objectproperties.backcols[5 * 4 + 3] = 1.0f;

    objectproperties.backcols[6 * 4 + 0] = 0.1f;
    objectproperties.backcols[6 * 4 + 1] = 0.5f;
    objectproperties.backcols[6 * 4 + 2] = 0.73f;
    objectproperties.backcols[6 * 4 + 3] = 1.0f;

    objectproperties.backcols[7 * 4 + 0] = 0.9f;
    objectproperties.backcols[7 * 4 + 1] = 0.5f;
    objectproperties.backcols[7 * 4 + 2] = 0.3f;
    objectproperties.backcols[7 * 4 + 3] = 1.0f;

    objectproperties.backcols[8 * 4 + 0] = 0.8f;
    objectproperties.backcols[8 * 4 + 1] = 0.8f;
    objectproperties.backcols[8 * 4 + 2] = 0.6f;
    objectproperties.backcols[8 * 4 + 3] = 1.0f;

    objectproperties.backcols[9 * 4 + 0] = 0.7f;
    objectproperties.backcols[9 * 4 + 1] = 0.9f;
    objectproperties.backcols[9 * 4 + 2] = 0.93f;
    objectproperties.backcols[9 * 4 + 3] = 1.0f;

    objectproperties.frontcol[0] = objectproperties.frontcols[0] = 0.9f;
    objectproperties.frontcol[1] = objectproperties.frontcols[1] = 0.6f;
    objectproperties.frontcol[2] = objectproperties.frontcols[2] = 0.1f;
    objectproperties.frontcol[3] = objectproperties.frontcols[3] = 1.0f;

    objectproperties.frontcols[1 * 4 + 0] = 0.3f;
    objectproperties.frontcols[1 * 4 + 1] = 0.8f;
    objectproperties.frontcols[1 * 4 + 2] = 0.5f;
    objectproperties.frontcols[1 * 4 + 3] = 1.0f;

    objectproperties.frontcols[2 * 4 + 0] = 0.2f;
    objectproperties.frontcols[2 * 4 + 1] = 0.5f;
    objectproperties.frontcols[2 * 4 + 2] = 0.6f;
    objectproperties.frontcols[2 * 4 + 3] = 1.0f;

    objectproperties.frontcols[3 * 4 + 0] = 0.1f;
    objectproperties.frontcols[3 * 4 + 1] = 0.3f;
    objectproperties.frontcols[3 * 4 + 2] = 0.9f;
    objectproperties.frontcols[3 * 4 + 3] = 1.0f;

    objectproperties.frontcols[4 * 4 + 0] = 0.96f;
    objectproperties.frontcols[4 * 4 + 1] = 0.71f;
    objectproperties.frontcols[4 * 4 + 2] = 0.3f;
    objectproperties.frontcols[4 * 4 + 3] = 1.0f;

    objectproperties.frontcols[5 * 4 + 0] = 0.4f;
    objectproperties.frontcols[5 * 4 + 1] = 0.4f;
    objectproperties.frontcols[5 * 4 + 2] = 0.9f;
    objectproperties.frontcols[5 * 4 + 3] = 1.0f;

    objectproperties.frontcols[6 * 4 + 0] = 0.99f;
    objectproperties.frontcols[6 * 4 + 1] = 0.1f;
    objectproperties.frontcols[6 * 4 + 2] = 0.843f;
    objectproperties.frontcols[6 * 4 + 3] = 1.0f;

    objectproperties.frontcols[7 * 4 + 0] = 0.16f;
    objectproperties.frontcols[7 * 4 + 1] = 0.91f;
    objectproperties.frontcols[7 * 4 + 2] = 0.73f;
    objectproperties.frontcols[7 * 4 + 3] = 1.0f;

    objectproperties.frontcols[8 * 4 + 0] = 0.8f;
    objectproperties.frontcols[8 * 4 + 1] = 0.9f;
    objectproperties.frontcols[8 * 4 + 2] = 0.0f;
    objectproperties.frontcols[8 * 4 + 3] = 1.0f;

    objectproperties.frontcols[9 * 4 + 0] = 0.9f;
    objectproperties.frontcols[9 * 4 + 1] = 0.91f;
    objectproperties.frontcols[9 * 4 + 2] = 0.3f;
    objectproperties.frontcols[9 * 4 + 3] = 1.0f;
    objectproperties.gridplanliste = 1;
    objectproperties.border = 1;
    objectproperties.mesh = 1;
    objectproperties.activarecnd = true;
    objectproperties.specReflection[0] = objectproperties.specReflection[1] =
            objectproperties.specReflection[2] = 0.2f;
    objectproperties.specReflection[3] = 1.0;
    objectproperties.shininess = 110;
    objectproperties.fill = 1;
    objectproperties.line = 1;
    objectproperties.infos = 1;
    objectproperties.frame = -1;
    objectproperties.infosdetails[0] = objectproperties.infosdetails[1] =
                                           objectproperties.infosdetails[2] = 1;
    objectproperties.boundingbox = -1;
    objectproperties.triangles = -1;
    objectproperties.typedrawing = 1;
    objectproperties.smoothline = -1;
    objectproperties.anim = -1;
    objectproperties.animx = -1;
    objectproperties.animy = -1;
    objectproperties.animz = -1;
    objectproperties.animxyz = 1;
    objectproperties.animxValue = objectproperties.animyValue =
                                      objectproperties.animzValue = 0.0;
    objectproperties.animxValueStep = objectproperties.animyValueStep =
                                          objectproperties.animzValueStep = 0.0;
    objectproperties.slider = -1;
    objectproperties.morph = -1;
    objectproperties.morphstep = -1;
    objectproperties.norm = -1;
    objectproperties.plan = 1;
    objectproperties.transparency = -1;
    objectproperties.png_ok = 1;
    objectproperties.jpg_ok = objectproperties.bmp_ok = -1;
    objectproperties.quality_image = 50;
    objectproperties.colortype = 0;
    objectproperties.colortypeParam = 0;
    InitComponentinfos(objectproperties.componentsinfos);
}

void ObjectParameters::InitComponentinfos(struct ComponentInfos &compinfos)
{
    for (int i = 0; i < 2; i++)
    {
        compinfos.NoiseParam[i].Octaves = 4;
        compinfos.NoiseParam[i].Lacunarity = 0.5;
        compinfos.NoiseParam[i].Gain = 0.5;
        compinfos.NoiseParam[i].NoiseActive = 1;
    }
}
