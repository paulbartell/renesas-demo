#if ( OTA_PAL_TEST_ENABLED == 1 )
void SetupOtaPalTestParam( OtaPalTestParam_t * pTestParam )
{
    pTestParam->pageSize = 1 << otaconfigLOG2_FILE_BLOCK_SIZE;
}
#endif /* if ( OTA_PAL_TEST_ENABLED == 1 ) */