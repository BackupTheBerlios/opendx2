///////////////////////////////////////////////////////////////////////
//                        DX  SOURCEFILE                             //
//                                                                   //
///////////////////////////////////////////////////////////////////////

//
// $Header: /home/xubuntu/berlios_backup/github/tmp-cvs/opendx2/Repository/dx/src/exec/libdx/groupinterpClass.X,v 1.1 1999/03/24 15:18:38 gda Exp $
//


typedef struct groupinterpolator *GroupInterpolator;

INCLUDE  interpClass.X

SUBCLASS    GroupInterpolator     OF Interpolator
IMPLEMENTS Interpolate Delete Copy LocalizeInterpolator

GroupInterpolator NewGroupInterpolator(Group, enum interp_init, float fuzz);

struct groupinterpolator
{
    struct interpolator	interpolator;
    int			nMembers;
    Interpolator	*subInterp;
    Interpolator	hint;
};

GroupInterpolator _dxfNewGroupInterpolator(Group,
			enum interp_init, float, Matrix *);

GroupInterpolator _dxf_NewGroupInterpolator(Group, enum interp_init,
			float, Matrix *, struct groupinterpolator_class *);

GroupInterpolator _dxf_CopyGroupInterpolator(GroupInterpolator,
			GroupInterpolator, enum copy copy);
