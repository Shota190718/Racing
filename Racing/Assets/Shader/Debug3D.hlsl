// �萔�o�b�t�@(CPU������̒l�󂯎���)
cbuffer global
{
	float4x4	WVP;    // �ϊ��s��
};

// ���_�V�F�[�_
float4 VS(float4 pos : POSITION) : SV_POSITION
{
	return mul(pos, WVP);	
}

// �s�N�Z���V�F�[�_
float4 PS(float4 pos : SV_POSITION) : SV_Target
{
	return float4(1, 1, 1, 0.3);
}