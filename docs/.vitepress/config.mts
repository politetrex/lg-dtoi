import { defineConfig } from 'vitepress'

// https://vitepress.dev/reference/site-config
export default defineConfig({
  base: '/lg-dtoi/',
  title: "DTOI守夜人团队",
  description: "DTOI守夜人团队官网",
  head: [
    ['link', { rel: 'icon', href: 'https://cdn.luogu.com.cn/upload/image_hosting/qer5jnsz.png' }],
    ['link', { rel: 'shortcut icon', href: 'https://cdn.luogu.com.cn/upload/image_hosting/qer5jnsz.png' }]
  ],
  themeConfig: {
    // https://vitepress.dev/reference/default-theme-config
    nav: [
      { text: '主页', link: '/' },
      { text: '项目',
        items: [
          {
            text: '娱乐项目',
            items: [
              { text: '迷宫', link: '/projects/1' },
              { text: 'ADV项目', link: '/projects/2' },
              { text: '赚钱小游戏', link: '/projects/3' }
            ]
          },
          {
            text: '其他项目',
            items: [
              { text: '其他', link: '/projects/other' }
            ]
          }
        ]
      },
      {
        text: '成员',
        items: [
            { text: '成员总览', link: '/users/all' },
            { text: '管理员', link: '/users/1' },
            { text: '开发主力', link: '/users/2' },
            { text: '队员', link: '/users/3' },
            { text: '疑似退役', link: '/users/4' },
            { text: '缅怀退役', link: '/users/5' }
        ]
      },
      { text: '实时文件区', link: '/livefilearea' }
    ],

    sidebar: {
      '/projects/':
      [
        {
          text: '娱乐项目',
          items: [
            { text: '迷宫', link: '/projects/1' },
            { text: 'ADV项目', link: '/projects/2' },
            { text: '赚钱小游戏', link: '/projects/3' }
          ]
        },
        {
          text: '其他项目',
          items: [
            { text: '其他', link: '/projects/other' }
          ]
        }
      ],
      '/users/':
      [
        {
            text: '成员',
            link: '/users/all',
            items: [
                { text: '管理员', link: '/users/1' },
                { text: '开发主力', link: '/users/2' },
                { text: '队员', link: '/users/3' },
                { text: '疑似退役', link: '/users/4' },
                { text: '缅怀退役', link: '/users/5' }
            ]
        }
      ],
      '/livefilearea':
      [
        {
            text: '实时文件区',
            link: '/livefilearea'
        }
    ]
    },

    socialLinks: [
      { icon: 'luogu', link: 'https://www.luogu.com.cn/team/118648' },
      { icon: 'github', link: 'https://github.com/politetrex/lg-dtoi' }
    ]
  }
})
