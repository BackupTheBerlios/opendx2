/*********************************************************************/
/*                        DX  SOURCEFILE                             */
/*********************************************************************/

#ifndef	hwMaterials_h
#define	hwMaterials_h


materialO _dxf_newHwMaterial(float ka, float kd, float ks, float sp);
materialO _dxf_getHwMaterialInfo(materialO mo,
		    float *ka, float *kd, float *ks, float *sp);
materialO _dxf_setHwMaterialAmbient(materialO mo, float ka);
materialO _dxf_setHwMaterialDiffuse(materialO mo, float kd);
materialO _dxf_setHwMaterialSpecular(materialO mo, float ks);
materialO _dxf_setHwMaterialShininess(materialO mo, float sp);


#endif /* hwMaterials_h */


