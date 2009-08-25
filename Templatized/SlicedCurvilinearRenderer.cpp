/***********************************************************************
SlicedCurvilinearRenderer - Class to render sliced curvilinear data
sets. Implemented as a specialization of the generic DataSetRenderer
class. Evil hack to test SlicedCurvilinear class; needs to be joined
with regular CurvilinearRenderer, since neither uses data values.
Copyright (c) 2008 Oliver Kreylos

This file is part of the 3D Data Visualizer (Visualizer).

The 3D Data Visualizer is free software; you can redistribute it and/or
modify it under the terms of the GNU General Public License as published
by the Free Software Foundation; either version 2 of the License, or (at
your option) any later version.

The 3D Data Visualizer is distributed in the hope that it will be
useful, but WITHOUT ANY WARRANTY; without even the implied warranty of
MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU
General Public License for more details.

You should have received a copy of the GNU General Public License along
with the 3D Data Visualizer; if not, write to the Free Software
Foundation, Inc., 59 Temple Place, Suite 330, Boston, MA 02111-1307 USA
***********************************************************************/

#define VISUALIZATION_TEMPLATIZED_SLICEDCURVILINEARRENDERER_IMPLEMENTATION

#include <Misc/ThrowStdErr.h>
#include <GL/GLContextData.h>
#include <GL/GLGeometryWrappers.h>

#include <Templatized/SlicedCurvilinearRenderer.h>

namespace Visualization {

namespace Templatized {

namespace SlicedCurvilinearRendererImplementation {

/*************************************************************************
Internal helper class to render curvilinear grids of different dimensions:
*************************************************************************/

template <class ScalarParam,int dimensionParam,class ValueScalarParam>
class GridRenderer
	{
	/* Dummy class; only dimension-specializations make sense */
	};

template <class ScalarParam,class ValueScalarParam>
class GridRenderer<ScalarParam,2,ValueScalarParam>
	{
	/* Embedded classes: */
	public:
	typedef SlicedCurvilinear<ScalarParam,2,ValueScalarParam> DataSet;
	typedef typename DataSet::Box Box;
	typedef typename DataSet::GridArray GridArray;
	typedef typename DataSet::Index Index;
	typedef typename DataSet::Cell Cell;
	
	/* Methods: */
	inline static void renderBoundingBox(const Box& box)
		{
		glBegin(GL_LINE_LOOP);
		glVertex(box.getVertex(0));
		glVertex(box.getVertex(1));
		glVertex(box.getVertex(3));
		glVertex(box.getVertex(2));
		glEnd();
		}
	inline static void renderGridOutline(const GridArray& grid)
		{
		/* Get vertex array size: */
		const Index& numVertices=grid.getSize();
		
		Index index;
		
		/* Render grid's outline: */
		glBegin(GL_LINE_STRIP);
		index[1]=0;
		for(index[0]=0;index[0]<numVertices[0];++index[0])
			glVertex(grid(index));
		glEnd();
		glBegin(GL_LINE_STRIP);
		index[1]=numVertices[1]-1;
		for(index[0]=0;index[0]<numVertices[0];++index[0])
			glVertex(grid(index));
		glEnd();
		glBegin(GL_LINE_STRIP);
		index[0]=0;
		for(index[1]=0;index[1]<numVertices[1];++index[1])
			glVertex(grid(index));
		glEnd();
		glBegin(GL_LINE_STRIP);
		index[0]=numVertices[0]-1;
		for(index[1]=0;index[1]<numVertices[1];++index[1])
			glVertex(grid(index));
		glEnd();
		}
	inline static void renderGridFaces(const GridArray& grid)
		{
		/* Get vertex array size: */
		const Index& numVertices=grid.getSize();
		
		Index index;
		
		/* Render grid's faces: */
		glBegin(GL_LINE_STRIP);
		index[1]=0;
		for(index[0]=0;index[0]<numVertices[0];++index[0])
			glVertex(grid(index));
		glEnd();
		glBegin(GL_LINE_STRIP);
		index[1]=numVertices[1]-1;
		for(index[0]=0;index[0]<numVertices[0];++index[0])
			glVertex(grid(index));
		glEnd();
		glBegin(GL_LINE_STRIP);
		index[0]=0;
		for(index[1]=0;index[1]<numVertices[1];++index[1])
			glVertex(grid(index));
		glEnd();
		glBegin(GL_LINE_STRIP);
		index[0]=numVertices[0]-1;
		for(index[1]=0;index[1]<numVertices[1];++index[1])
			glVertex(grid(index));
		glEnd();
		}
	inline static void renderGridCells(const GridArray& grid)
		{
		/* Get vertex array size: */
		const Index& numVertices=grid.getSize();
		
		Index index;
		
		/* Render grid lines along x direction: */
		for(index[1]=0;index[1]<numVertices[1];++index[1])
			{
			glBegin(GL_LINE_STRIP);
			for(index[0]=0;index[0]<numVertices[0];++index[0])
				glVertex(grid(index));
			glEnd();
			}
		
		/* Render grid lines along y direction: */
		for(index[0]=0;index[0]<numVertices[0];++index[0])
			{
			glBegin(GL_LINE_STRIP);
			for(index[1]=0;index[1]<numVertices[1];++index[1])
				glVertex(grid(index));
			glEnd();
			}
		}
	inline static void highlightCell(const Cell& cell)
		{
		glBegin(GL_LINE_LOOP);
		glVertex(cell.getVertexPosition(0));
		glVertex(cell.getVertexPosition(1));
		glVertex(cell.getVertexPosition(3));
		glVertex(cell.getVertexPosition(2));
		glEnd();
		}
	};

template <class ScalarParam,class ValueScalarParam>
class GridRenderer<ScalarParam,3,ValueScalarParam>
	{
	/* Embedded classes: */
	public:
	typedef SlicedCurvilinear<ScalarParam,3,ValueScalarParam> DataSet;
	typedef typename DataSet::Point Point;
	typedef typename DataSet::Box Box;
	typedef typename DataSet::GridArray GridArray;
	typedef typename DataSet::Index Index;
	typedef typename DataSet::Cell Cell;
	
	/* Methods: */
	inline static void renderBoundingBox(const Box& box)
		{
		glBegin(GL_LINE_STRIP);
		glVertex(box.getVertex(0));
		glVertex(box.getVertex(1));
		glVertex(box.getVertex(3));
		glVertex(box.getVertex(2));
		glVertex(box.getVertex(0));
		glVertex(box.getVertex(4));
		glVertex(box.getVertex(5));
		glVertex(box.getVertex(7));
		glVertex(box.getVertex(6));
		glVertex(box.getVertex(4));
		glEnd();
		glBegin(GL_LINES);
		glVertex(box.getVertex(1));
		glVertex(box.getVertex(5));
		glVertex(box.getVertex(3));
		glVertex(box.getVertex(7));
		glVertex(box.getVertex(2));
		glVertex(box.getVertex(6));
		glEnd();
		}
	inline static void renderGridLine(const GridArray& grid,const Index& startIndex,int axis)
		{
		/* Get pointer to first grid vertex: */
		const Point* vPtr=grid.getAddress(startIndex);
		int numVertices=grid.getSize(axis);
		int stride=grid.getIncrement(axis);
		
		/* Render grid line: */
		glBegin(GL_LINE_STRIP);
		for(int i=0;i<numVertices;++i,vPtr+=stride)
			glVertex(*vPtr);
		glEnd();
		}
	inline static void renderGridOutline(const GridArray& grid)
		{
		/* Get vertex array size: */
		const Index& numVertices=grid.getSize();
		
		/* Render grid outlines: */
		renderGridLine(grid,Index(0,0,0),0);
		renderGridLine(grid,Index(0,numVertices[1]-1,0),0);
		renderGridLine(grid,Index(0,numVertices[1]-1,numVertices[2]-1),0);
		renderGridLine(grid,Index(0,0,numVertices[2]-1),0);
		renderGridLine(grid,Index(0,0,0),1);
		renderGridLine(grid,Index(numVertices[0]-1,0,0),1);
		renderGridLine(grid,Index(numVertices[0]-1,0,numVertices[2]-1),1);
		renderGridLine(grid,Index(0,0,numVertices[2]-1),1);
		renderGridLine(grid,Index(0,0,0),2);
		renderGridLine(grid,Index(numVertices[0]-1,0,0),2);
		renderGridLine(grid,Index(numVertices[0]-1,numVertices[1]-1,0),2);
		renderGridLine(grid,Index(0,numVertices[1]-1,0),2);
		}
	inline static void renderGridFaces(const GridArray& grid)
		{
		/* Get vertex array size: */
		const Index& numVertices=grid.getSize();
		
		Index index;
		
		/* Render grid lines in (x,y)-plane: */
		index[0]=0;
		for(index[1]=0;index[1]<numVertices[1];++index[1])
			{
			index[2]=0;
			renderGridLine(grid,index,0);
			index[2]=numVertices[2]-1;
			renderGridLine(grid,index,0);
			}
		index[1]=0;
		for(index[0]=0;index[0]<numVertices[0];++index[0])
			{
			index[2]=0;
			renderGridLine(grid,index,1);
			index[2]=numVertices[2]-1;
			renderGridLine(grid,index,1);
			}
		
		/* Render grid lines in (x,z)-plane: */
		index[0]=0;
		for(index[2]=0;index[2]<numVertices[2];++index[2])
			{
			index[1]=0;
			renderGridLine(grid,index,0);
			index[1]=numVertices[1]-1;
			renderGridLine(grid,index,0);
			}
		index[2]=0;
		for(index[0]=0;index[0]<numVertices[0];++index[0])
			{
			index[1]=0;
			renderGridLine(grid,index,2);
			index[1]=numVertices[1]-1;
			renderGridLine(grid,index,2);
			}
		
		/* Render grid lines in (y,z)-plane: */
		index[1]=0;
		for(index[2]=0;index[2]<numVertices[2];++index[2])
			{
			index[0]=0;
			renderGridLine(grid,index,1);
			index[0]=numVertices[0]-1;
			renderGridLine(grid,index,1);
			}
		index[2]=0;
		for(index[1]=0;index[1]<numVertices[1];++index[1])
			{
			index[0]=0;
			renderGridLine(grid,index,2);
			index[0]=numVertices[0]-1;
			renderGridLine(grid,index,2);
			}
		}
	inline static void renderGridCells(const GridArray& grid)
		{
		/* Get vertex array size: */
		const Index& numVertices=grid.getSize();
		
		Index index;
		
		/* Render grid lines along x-axis: */
		index[0]=0;
		for(index[1]=0;index[1]<numVertices[1];++index[1])
			for(index[2]=0;index[2]<numVertices[2];++index[2])
				renderGridLine(grid,index,0);
		
		/* Render grid lines along y-axis: */
		index[1]=0;
		for(index[0]=0;index[0]<numVertices[0];++index[0])
			for(index[2]=0;index[2]<numVertices[2];++index[2])
				renderGridLine(grid,index,1);
		
		/* Render grid lines along z-axis: */
		index[2]=0;
		for(index[0]=0;index[0]<numVertices[0];++index[0])
			for(index[1]=0;index[1]<numVertices[1];++index[1])
				renderGridLine(grid,index,2);
		}
	inline static void highlightCell(const Cell& cell)
		{
		glBegin(GL_LINE_STRIP);
		glVertex(cell.getVertexPosition(0));
		glVertex(cell.getVertexPosition(1));
		glVertex(cell.getVertexPosition(3));
		glVertex(cell.getVertexPosition(2));
		glVertex(cell.getVertexPosition(0));
		glVertex(cell.getVertexPosition(4));
		glVertex(cell.getVertexPosition(5));
		glVertex(cell.getVertexPosition(7));
		glVertex(cell.getVertexPosition(6));
		glVertex(cell.getVertexPosition(4));
		glEnd();
		glBegin(GL_LINES);
		glVertex(cell.getVertexPosition(1));
		glVertex(cell.getVertexPosition(5));
		glVertex(cell.getVertexPosition(3));
		glVertex(cell.getVertexPosition(7));
		glVertex(cell.getVertexPosition(2));
		glVertex(cell.getVertexPosition(6));
		glEnd();
		}
	};

}

/***************************************************
Methods of class DataSetRenderer<SlicedCurvilinear>:
***************************************************/

template <class ScalarParam,int dimensionParam,class ValueScalarParam>
inline
DataSetRenderer<SlicedCurvilinear<ScalarParam,dimensionParam,ValueScalarParam> >::DataSetRenderer(
	const typename DataSetRenderer<SlicedCurvilinear<ScalarParam,dimensionParam,ValueScalarParam> >::DataSet* sDataSet)
	:dataSet(sDataSet),
	 renderingModeIndex(0)
	{
	}

template <class ScalarParam,int dimensionParam,class ValueScalarParam>
inline
DataSetRenderer<SlicedCurvilinear<ScalarParam,dimensionParam,ValueScalarParam> >::~DataSetRenderer(
	void)
	{
	/* Nothing to do yet... */
	}

template <class ScalarParam,int dimensionParam,class ValueScalarParam>
inline
int
DataSetRenderer<SlicedCurvilinear<ScalarParam,dimensionParam,ValueScalarParam> >::getNumRenderingModes(
	void)
	{
	return 4;
	}

template <class ScalarParam,int dimensionParam,class ValueScalarParam>
inline
const char*
DataSetRenderer<SlicedCurvilinear<ScalarParam,dimensionParam,ValueScalarParam> >::getRenderingModeName(
	int renderingModeIndex)
	{
	if(renderingModeIndex<0||renderingModeIndex>=4)
		Misc::throwStdErr("DataSetRenderer::getRenderingModeName: invalid rendering mode index %d",renderingModeIndex);
	
	static const char* renderingModeNames[4]=
		{
		"Bounding Box","Grid Outline","Grid Faces","Grid Cells"
		};
	
	return renderingModeNames[renderingModeIndex];
	}

template <class ScalarParam,int dimensionParam,class ValueScalarParam>
inline
void
DataSetRenderer<SlicedCurvilinear<ScalarParam,dimensionParam,ValueScalarParam> >::setRenderingMode(
	int newRenderingModeIndex)
	{
	if(newRenderingModeIndex<0||newRenderingModeIndex>=4)
		Misc::throwStdErr("DataSetRenderer::setRenderingMode: invalid rendering mode index %d",newRenderingModeIndex);
	
	renderingModeIndex=newRenderingModeIndex;
	}

template <class ScalarParam,int dimensionParam,class ValueScalarParam>
inline
void
DataSetRenderer<SlicedCurvilinear<ScalarParam,dimensionParam,ValueScalarParam> >::glRenderAction(
	GLContextData& contextData) const
	{
	switch(renderingModeIndex)
		{
		case 0:
			/* Render the grid's bounding box: */
			SlicedCurvilinearRendererImplementation::GridRenderer<ScalarParam,dimensionParam,ValueScalarParam>::renderBoundingBox(dataSet->getDomainBox());
			break;
		
		case 1:
			/* Render the grid's outline: */
			SlicedCurvilinearRendererImplementation::GridRenderer<ScalarParam,dimensionParam,ValueScalarParam>::renderGridOutline(dataSet->getGrid());
			break;
		
		case 2:
			/* Render the grid's faces: */
			SlicedCurvilinearRendererImplementation::GridRenderer<ScalarParam,dimensionParam,ValueScalarParam>::renderGridFaces(dataSet->getGrid());
			break;
		
		case 3:
			/* Render the grid's cells: */
			SlicedCurvilinearRendererImplementation::GridRenderer<ScalarParam,dimensionParam,ValueScalarParam>::renderGridCells(dataSet->getGrid());
			break;
		}
	}

template <class ScalarParam,int dimensionParam,class ValueScalarParam>
inline
void
DataSetRenderer<SlicedCurvilinear<ScalarParam,dimensionParam,ValueScalarParam> >::renderCell(
	const typename DataSetRenderer<SlicedCurvilinear<ScalarParam,dimensionParam,ValueScalarParam> >::CellID& cellID,
	GLContextData& contextData) const
	{
	/* Highlight the cell: */
	SlicedCurvilinearRendererImplementation::GridRenderer<ScalarParam,dimensionParam,ValueScalarParam>::highlightCell(dataSet->getCell(cellID));
	}

}

}