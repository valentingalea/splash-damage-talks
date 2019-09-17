#! /bin/bash

npm run build_std
mv surf_std/* ../docs/surf_std/

npm run build_std_tags
mv surf_std_tags/* ../docs/surf_std_tags/

npm run build_std_layout
mv surf_std_layout/* ../docs/surf_std_layout/

npm run build_std_braces
mv surf_std_braces/* ../docs/surf_std_braces/

npm run build_std_auto
mv surf_std_auto/* ../docs/surf_std_auto/

npm run build_std_lambda
mv surf_std_lambda/* ../docs/surf_std_lambda/

npm run build_std_memory
mv surf_std_memory/* ../docs/surf_std_memory/