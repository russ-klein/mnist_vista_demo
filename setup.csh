# Local tools
#

setenv VISTA_VERSION      vista2021_3
setenv CATAPULT_VERSION   2021.1_1

setenv VISTA_ROOT    /project/codelink/tools/vista/{$VISTA_VERSION}/install
setenv CATAPULT_HOME /wv/hlsb/CATAPULT/{$CATAPULT_VERSION}/PRODUCTION/aol/Mgc_home
setenv MATCHLIB_HOME $CATAPULT_HOME/shared/examples/matchlib

setenv PATH {$PATH}:$VISTA_ROOT/bin:$CATAPULT_HOME/bin
