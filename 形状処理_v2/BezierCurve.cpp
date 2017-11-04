#include "BezierCurve.h"
#include "ControlPoint.h"

BezierCurve::BezierCurve(int mord, ControlPoint* cp, int cp_size, GLdouble* color, GLdouble width)
{
    _ord = mord;
    _ncpnt = cp_size;

    SetControlPoint(cp, cp_size);
    SetColor(color);
    _width = width;

    // VBOg¤
    _isUseVBO = true;
}

// O`æ
void BezierCurve::PreDraw()
{
    glColor3dv(_color);
    glLineWidth(_width);

    glBegin(GL_LINE_STRIP);

    for (int i = 0; i <= 100; i += 1)
    {
        double t = (double)i / 100;
        Vector3d pnt = GetPositionVector(t);

        glVertex3d(pnt);
    }

    glEnd();
}

// ¸_obt@ì¬
void BezierCurve::CreateVBO()
{
    vector<Vector3d> pnts;

    // ¸_æ¾
    for (int i = 0; i <= 100; i += 1)
    {
        double t = (double)i / 100;
        pnts.push_back(GetPositionVector(t));
    }

    _nVertex = (int)pnts.size();

    glGenBuffers(1, &_vbo);
    glBindBuffer(GL_ARRAY_BUFFER, _vbo);
    glBufferData(GL_ARRAY_BUFFER, pnts.size() * 3 * sizeof(double), (GLdouble*)&pnts[0], GL_DYNAMIC_DRAW);
}

// VBOÅ`æ
void BezierCurve::DrawVBO()
{
    glColor3dv(_color);
    glLineWidth(_width);

    glBindBuffer(GL_ARRAY_BUFFER, _vbo);
    glVertexPointer(3, GL_DOUBLE, 0, 0);

    glEnableClientState(GL_VERTEX_ARRAY);

    glDrawArrays(GL_LINE_STRIP, 0, _nVertex);

    glDisableClientState(GL_VERTEX_ARRAY);
    glBindBuffer(GL_ARRAY_BUFFER, 0);
}

// ÚüxNg`æ
void BezierCurve::DrawFirstDiffVectorsInternal()
{
    Vector3d pnt, diff;

    glColor3dv(Color::red);
    glLineWidth(1.0);
    glBegin(GL_LINES);

    for (int i = 0; i <= 100; i += 5)
    {
        double t = (double)i / 100;

        pnt = GetPositionVector(t);
        diff = GetFirstDiffVector(t).Normalize();
        glVertex3d(pnt);
        glVertex3d(pnt + diff);
    }

    glEnd();
}

// 2K÷ªxNg`æ
void BezierCurve::DrawSecondDiffVectorsInternal()
{
    Vector3d pnt, diff;

    glColor3dv(Color::blue);
    glLineWidth(1.0);
    glBegin(GL_LINES);

    for (int i = 0; i <= 100; i += 5)
    {
        double t = (double)i / 100;

        pnt = GetPositionVector(t);
        diff = GetSecondDiffVector(t).Normalize();
        glVertex3d(pnt);
        glVertex3d(pnt + diff);
    }

    glEnd();
}

// @üxNg`æ
void BezierCurve::DrawNormalVectorsInternal()
{
    Vector3d pnt, normal;

    glColor3dv(Color::blue);
    glLineWidth(1.0);
    glBegin(GL_LINES);

    for (int i = 0; i <= 100; i += 5)
    {
        double t = (double)i / 100;

        pnt = GetPositionVector(t);
        normal = GetNormalVector(t).Normalize();
        glVertex3d(pnt);
        glVertex3d(pnt + normal);
    }

    glEnd();
}

// È¦¼a`æ
void BezierCurve::DrawCurvatureVectorsInternal()
{
    Vector3d pnt, curv;

    glLineWidth(1.0);
    glPointSize(5.0);

    for (int i = 0; i <= 100; i += 2)
    {
        double t = (double)i / 100;

        pnt = GetPositionVector(t);
        curv = GetCurvatureVector(t);

        // È¦¼a`æ
        glColor3dv(Color::pink);
        glBegin(GL_LINES);
        glVertex3d(pnt);
        glVertex3d(pnt + curv);
        glEnd();

        // È¦S`æ
        glColor3dv(Color::light_green);
        glBegin(GL_POINTS);
        glVertex3d(pnt + curv);
        glEnd();
    }
}

// ÊuxNgæ¾
Vector3d BezierCurve::GetPositionVector(double t)
{
    Vector3d pnt;

    for (int i = 0; i < _ncpnt; i++)
        pnt += CalcBernsteinFunc(i, _ord - 1, t) * _ctrlp[i];

    return pnt;
}

// ÚüxNgæ¾
Vector3d BezierCurve::GetFirstDiffVector(double t)
{
    Vector3d diff;

    for (int i = 0; i < _ncpnt; i++)
        diff += Calc1DiffBernsteinFunc(i, _ord - 1, t) * _ctrlp[i];

    return diff;
}

// 2K÷ªxNgæ¾
Vector3d BezierCurve::GetSecondDiffVector(double t)
{
    Vector3d diff;

    for (int i = 0; i < _ncpnt; i++)
        diff += Calc2DiffBernsteinFunc(i, _ord - 1, t) * _ctrlp[i];

    return diff;
}
