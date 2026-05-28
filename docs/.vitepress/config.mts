import { defineConfig } from 'vitepress'

// https://vitepress.dev/reference/site-config
export default defineConfig({
  base: '/lg-dtoi/',
  title: "DTOI守夜人团队",
  description: "DTOI守夜人团队官网",
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
      }
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
      ]
    },

    socialLinks: [
      { icon: 'luogu', link: 'https://www.luogu.com.cn/team/118648' }
    ]
  }
})
